#include "gabor.hpp"

int MODULO(int a, int b) {
#pragma HLS inline
	//negative mod is not defined very well
	int res = a % b;
	return res < 0 ? res + b : res;
}

//------------------------------------------------------------------------------------
//					Gabor Kernel Float
//-----------------------------------------------------------------------------------

void generateGaussKernel(int kern_size,
		float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	int peak = 8;
	float alpha = (kern_size - 1) * 0.4770322291;
	float alphaPower = alpha * alpha;
	CreateGauss: for (int i = 0; i < kern_size; i++) {
		float rho = i - ((float) kern_size / 2.0);
		float rhoPower2 = rho * rho;
		CreateGaussInner: for (int j = 0; j < kern_size; j++) {
			float phi = j - ((float) kern_size / 2.0);
			float temp1 = -(rhoPower2 + phi * phi) / alphaPower;
			float temp = peak * hls::expf(temp1);
			gauss[i][j] = temp;
		}
	}
}

void generateGaborKernel(int kern_size,
		float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {

	if (kern_size > MAX_KERN_SIZE)
		kern_size = MAX_KERN_SIZE;

	float sum_row_sin = 0;
	float sum_row_cos = 0;
	CalcFirstRow:
	for (int i = 0; i < kern_size; i++) {
		int phi = i - (kern_size / 2);
		int temp = kern_size / 2;
		float val_sin;
		float val_cos;
		cordic360_COS_SIN(PI * phi / temp, val_sin, val_cos, 5);

		sin_filter_matrix[0][i] = val_sin;
		cos_filter_matrix[0][i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}

	NormalizeFirstRow:
	for (int i = 0; i < kern_size; i++) {
		float old_v_s = sin_filter_matrix[0][i];
		float old_v_c = cos_filter_matrix[0][i];
		sin_filter_matrix[0][i] = old_v_s - (sum_row_sin / (float) kern_size);
		cos_filter_matrix[0][i] = old_v_c - (sum_row_cos / (float) kern_size);
	}

	AssignCompleteMatrix:
	for (int i = 1; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[0][j];
			cos_filter_matrix[i][j] = cos_filter_matrix[0][j];
		}
	}
	float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	generateGaussKernel(kern_size,gauss);

	GaussMulti:
	for (int i = 0; i < kern_size; i++) {
		float rho = i - (kern_size / 2);
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[i][j] * gauss[i][j];
			cos_filter_matrix[i][j] = cos_filter_matrix[i][j] * gauss[i][j];
		}
	}

	NormalizeGausGabor:
	for (int i = 0; i < kern_size; i++) {
		float row_sum_sin = 0;
		float row_sum_cos = 0;
		for (int j = 0; j < kern_size; j++) {
			row_sum_sin += sin_filter_matrix[i][j];
			row_sum_cos += cos_filter_matrix[i][j];
		}
		for (int j = 0; j < kern_size; j++) {
			float old_sin = sin_filter_matrix[i][j];
			float old_cos = cos_filter_matrix[i][j];
			sin_filter_matrix[i][j] = old_sin
					- (row_sum_sin / (float) kern_size);
			cos_filter_matrix[i][j] = old_cos
					- (row_sum_cos / (float) kern_size);
		}
	}
}

uint8_t gaborPixel(int rho, int phi, uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		int filter_size, float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	int angles = NORM_WIDTH;
	float total_i = 0.0;
	float total_r = 0.0;

	GaborPixeLoop:
	for (int i = 0; i < filter_size; i++) {
		for (int j = 0; j < filter_size; j++) {
			int image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y, angles);

			int image_x = i + rho - (filter_size / 2);
			int tmp = norm_img[image_x * NORM_WIDTH + image_y];
			total_i += sin_filter_matrix[i][j] * tmp;
			total_r += cos_filter_matrix[i][j] * tmp;
		}
	}
	//bitcode_t << 1;
	uint8_t ret = 0;
	if (total_r >= 0.0) {
		ret = 2;
		//bitcode_t |=1;
	} else {
		ret = 0;
		//bitcode_t |=0;
	}
	//bitcode_t << 1;
	if (total_i >= 0.0) {
		ret = ret | 1;
		//bitcode_t |=1;
	} else {
		ret = ret | 0;
		//bitcode_t |=0;
	}
	return ret;
}

void encode(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],uint8_t bit_code[BITCODE_LENGTH]){
	float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	int height = NORM_HEIGHT;
	int width  = NORM_WIDTH;

	int angular_slice = NORM_WIDTH;
	int radial_slice  = ENCODED_PIXELS / angular_slice;

	int max_filter = NORM_HEIGHT / 3;

	int index = 0;
//0,1
	for (int r_slice = 0 ;r_slice < radial_slice ;r_slice++){
		int radius = ((r_slice * (height - 6)) / (2 * radial_slice)) + 3;
		int filter_height;

		if (radius < (height - radius)){
			filter_height = 2 * radius - 1;
		}else{
			filter_height = 2 * (height - radius) - 1;
		}
		if (filter_height > max_filter) filter_height = max_filter;

		generateGaborKernel(filter_height,sin_filter_matrix,cos_filter_matrix);

		for (int theta = 0;theta<angular_slice;theta++){
			uint8_t temp = gaborPixel(radius,theta,norm_img,filter_height,sin_filter_matrix,cos_filter_matrix);
			bit_code[index]   = (temp & 2)>>1;//real
			bit_code[index+1] = temp & 1;//imag
			index+=2;
		}
	}
}


//------------------------------------------------------------------------------------
//					Gabor Kernel Fix Point
//-----------------------------------------------------------------------------------

template<int RESULT_W,int RESULT_H,int INTERN_W,int INTERN_H>
void generateGaussKernel_fix(int kern_size,
		ap_fixed<RESULT_W,RESULT_H> gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	int peak = 8;
	ap_fixed<INTERN_W,INTERN_H> alpha = (kern_size - 1) * 0.4770322291;
	ap_fixed<INTERN_W,INTERN_H> alphaPower = alpha * alpha;
	CreateGauss:
	for (int i = 0; i < kern_size; i++) {
		ap_fixed<INTERN_W,INTERN_H> rho = i - ((ap_fixed<INTERN_W,INTERN_H>) kern_size / (ap_fixed<INTERN_W,INTERN_H>)2.0);
		ap_fixed<INTERN_W,INTERN_H> rhoPower2 = rho * rho;
		CreateGaussInner: for (int j = 0; j < kern_size; j++) {
			ap_fixed<INTERN_W,INTERN_H> phi = j - ((ap_fixed<INTERN_W,INTERN_H>) kern_size / (ap_fixed<INTERN_W,INTERN_H>)2.0);
			ap_fixed<INTERN_W,INTERN_H> temp1 = -(rhoPower2 + phi * phi) / alphaPower;
			gauss[i][j] =  peak * hls::expf(temp1);
		}
	}
}

template<int RESULT_W,int RESULT_H,int INTERN_W,int INTERN_H>
void generateGaborKernel_fix(int kern_size,
		ap_fixed<RESULT_W, RESULT_H> sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		ap_fixed<RESULT_W, RESULT_H> cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {

	if (kern_size > MAX_KERN_SIZE)
		kern_size = MAX_KERN_SIZE;

	ap_fixed<INTERN_W,INTERN_H> sum_row_sin = 0;
	ap_fixed<INTERN_W,INTERN_H> sum_row_cos = 0; //max ~441
	CalcFirstRow:
	for (int i = 0; i < kern_size; i++) {
		int phi = i - ((ap_fixed<INTERN_W,INTERN_H>) kern_size / (ap_fixed<INTERN_W,INTERN_H>)2.0);
		int temp = kern_size / 2;
		ap_fixed<INTERN_W,INTERN_H> angle = PI * phi / temp;
		ap_fixed<INTERN_W,INTERN_H> val_sin;
		ap_fixed<INTERN_W,INTERN_H> val_cos;
		cordic360_COS_SIN_fix(angle, val_sin, val_cos, 5);
		sin_filter_matrix[0][i] = val_sin;
		cos_filter_matrix[0][i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}

	NormalizeFirstRow:
	for (int i = 0; i < kern_size; i++) {
		sin_filter_matrix[0][i] = sin_filter_matrix[0][i]
				- (ap_fixed<INTERN_W,INTERN_H>) (sum_row_sin / (ap_fixed<INTERN_W,INTERN_H>) kern_size);
		cos_filter_matrix[0][i] = cos_filter_matrix[0][i]
				- (ap_fixed<INTERN_W,INTERN_H>) (sum_row_cos / (ap_fixed<INTERN_W,INTERN_H>) kern_size);
	}

	AssignCompleteMatrix:
	for (int i = 1; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[0][j];
			cos_filter_matrix[i][j] = cos_filter_matrix[0][j];
		}
	}

	ap_fixed<RESULT_W, RESULT_H> gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	generateGaussKernel_fix<RESULT_W,RESULT_H,INTERN_W,INTERN_H>(kern_size,gauss);

	GaussMultiSine:
	for (int i = 0; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[i][j]
					* gauss[i][j];
			cos_filter_matrix[i][j] = cos_filter_matrix[i][j]
					* gauss[i][j];
		}
	}

	NormalizeGausGabor: for (int i = 0; i < kern_size; i++) {
		ap_fixed<INTERN_W,INTERN_H> row_sum_sin = 0;
		ap_fixed<INTERN_W,INTERN_H> row_sum_cos = 0;
		for (int j = 0; j < kern_size; j++) {
			row_sum_sin += sin_filter_matrix[i][j];
			row_sum_cos += cos_filter_matrix[i][j];
		}
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[i][j]
					- (row_sum_sin / (ap_fixed<INTERN_W,INTERN_H>) kern_size);
			cos_filter_matrix[i][j] = cos_filter_matrix[i][j]
					- (row_sum_cos / (ap_fixed<INTERN_W,INTERN_H>) kern_size);
		}
	}

}

template<int RESULT_W,int RESULT_H,int INTERN_W,int INTERN_H>
ap_uint<2> gaborPixel_fix(int rho, int phi, uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],int filter_size,
	ap_fixed<RESULT_W, RESULT_H> sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
	ap_fixed<RESULT_W, RESULT_H> cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]){
	ap_uint<9> angles = NORM_WIDTH;
	ap_fixed<INTERN_W,INTERN_H> total_i = 0.0;
	ap_fixed<INTERN_W,INTERN_H> total_r = 0.0;

	GaborPixeLoop:
	for (int i = 0; i<filter_size;i++){
		ap_uint<9> image_x =  i + rho - (filter_size / 2);
		for (int j = 0; j<filter_size;j++){
			ap_uint<9> image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y,angles);

			uint8_t tmp = norm_img[image_x*angles+image_y];
			total_i += sin_filter_matrix[i][j] * tmp;//255*6.4
			total_r += cos_filter_matrix[i][j] * tmp;
		}
	}
	//bitcode_t << 1;
	uint8_t ret = 0;
	if (total_r >= 0.0 ){
		ret = 2;
		//bitcode_t |=1;
	}else{
		ret = 0;
		//bitcode_t |=0;
	}
	//bitcode_t << 1;
	if (total_i >= 0.0 ){
		ret = ret | 1;
		//bitcode_t |=1;
	}else{
		ret = ret | 0;
		//bitcode_t |=0;
	}
	return ret;
}

//template<int RESULT_W,int RESULT_H,int INTERN_W,int INTERN_H>
//compiler error for template function no function body, without template okay. Why?
void encode_fix(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],uint8_t bit_code[BITCODE_LENGTH]){
	const int RESULT_W = 16;
	const int RESULT_H = 8;
	const int INTERN_W = 16;
	const int INTERN_H = 8;

	ap_fixed<RESULT_W, RESULT_H> sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	ap_fixed<RESULT_W, RESULT_H> cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	int height = NORM_HEIGHT;
	int width  = NORM_WIDTH;

	int angular_slice = NORM_WIDTH;
	int radial_slice  = ENCODED_PIXELS / angular_slice;

	int max_filter = NORM_HEIGHT / 3;

	int index = 0;
//0,1
	for (int r_slice = 0; r_slice < radial_slice; r_slice++) {
		int radius = ((r_slice * (height - 6)) / (2 * radial_slice)) + 3;
		int filter_height;

		if (radius < (height - radius)) {
			filter_height = 2 * radius - 1;
		} else {
			filter_height = 2 * (height - radius) - 1;
		}
		if (filter_height > max_filter)
			filter_height = max_filter;

		generateGaborKernel_fix<RESULT_W, RESULT_H, INTERN_W, INTERN_H>(
				filter_height, sin_filter_matrix, cos_filter_matrix);

		for (int theta = 0; theta < angular_slice; theta++) {
			int2 temp = gaborPixel_fix<RESULT_W, RESULT_H, INTERN_W, INTERN_H>(
					radius, theta, norm_img, filter_height, sin_filter_matrix,
					cos_filter_matrix);
			bit_code[index] = (temp & 2) >> 1; //real
			bit_code[index + 1] = temp & 1; //imag
			index += 2;
		}
	}
}
