#include "gabor.hpp"
#include <math.h>
int MODULO(int a, int b) {
#pragma HLS inline
	//negative mod is not defined very well
	int res = a % b;
	return res < 0 ? res + b : res;
}

//------------------------------------------------------------------------------------
//					Gabor Kernel Float
//-----------------------------------------------------------------------------------

void generateGaussKernel(int kern_size,int peak,
		float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	float alpha = (kern_size - 1) * 0.4770322291;
	float alphaPower = alpha * alpha;
	CreateGauss:
	for (int i = 0; i < kern_size; i++) {
		float rho = i - ((float) kern_size / 2.0);
		float rhoPower2 = rho * rho;
		for (int j = 0; j < kern_size; j++) {
			float phi = j - ((float) kern_size / 2.0);
			float temp1 = -(rhoPower2 + phi * phi) / alphaPower;
			float temp = peak * hls::expf(temp1);
			gauss[i][j] = temp;
		}
	}
}

void generateSinKernel(int kern_size,
		float sinK[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cosK[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	float sum_row_sin = 0;
	float sum_row_cos = 0;
	CalcFirstRow:
	for (int i = 0; i < kern_size; i++) {
		int phi = i - (kern_size / 2);
		int temp = kern_size / 2;
		float val_sin = sin(PI * phi / temp);
		float val_cos = cos(PI * phi / temp);
		//cordic360_COS_SIN(PI * phi / temp, val_sin, val_cos, 15);

		sinK[0][i] = val_sin;
		cosK[0][i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}

	NormalizeFirstRow:
	for (int i = 0; i < kern_size; i++) {
		float old_v_s = sinK[0][i];
		float old_v_c = cosK[0][i];
		sinK[0][i] = old_v_s - (sum_row_sin / (float) kern_size);
		cosK[0][i] = old_v_c - (sum_row_cos / (float) kern_size);
	}

	AssignCompleteMatrix:
	for (int i = 1; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sinK[i][j] = sinK[0][j];
			cosK[i][j] = cosK[0][j];
		}
	}
}

void generateGaborKernel(int kern_size,
		float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {

	if (kern_size > MAX_KERN_SIZE)
		kern_size = MAX_KERN_SIZE;
	float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];

	generateSinKernel(kern_size,sin_filter_matrix,cos_filter_matrix);
	generateGaussKernel(kern_size,8,gauss);

	GaussMulti:
	for (int i = 0; i < kern_size; i++) {
		float rho = i - (kern_size / 2);
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[i][j] * gauss[i][j];
			cos_filter_matrix[i][j] = cos_filter_matrix[i][j] * gauss[i][j];
		}
	}
/*
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
	}*/
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

	//std::cout << total_i <<"\n";
	//std::cout << total_r <<"\n";

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


void generateGaussKernel_fix(int kern_size, int peak,
		floatGauss gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	//Min/Max numbers are calc. with MAX_KERN_SIZE = 10 ->height = 32
	ap_ufixed<16, 5> alpha = (kern_size - 1) * 0.47703222; //2.38..4.77
	ap_ufixed<16, 5> alphaPower = alpha * alpha; //9..22.75
	ap_ufixed<16, 5> temp = ((ap_ufixed<16, 5> ) kern_size/ (ap_ufixed<16, 5> ) 2); //5
	CreateGauss:
	for (int i = 0; i < kern_size; i++) {
		ap_fixed<16, 6> rho = i - temp; //-5..-1
		ap_fixed<16, 6> rhoPower2 = rho * rho; //25..1
		for (int j = 0; j < kern_size; j++) {
			ap_fixed<16, 6> phi = j - temp; //-5..-1
			ap_fixed<16, 6> temp1 = -(rhoPower2 + phi * phi) / alphaPower; //2.19...0.79
			gauss[i][j] = peak * hls::exp(temp1);
		}
	}
}

void generateSinKernel_fix(int kern_size,
		floatSin sin[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatSin cos[MAX_KERN_SIZE][MAX_KERN_SIZE]) {
	//Min/Max numbers are calc. with MAX_KERN_SIZE = 10 ->height = 32

	ap_fixed<16,3> sum_row_sin = 0;
	ap_fixed<16,3> sum_row_cos = 0;
	CalcFirstRow:
	for (int i = 0; i < kern_size; i++) {
		int phi = i - ( kern_size / 2);
		int temp = kern_size / 2;
		floatArg angle = PI * phi / temp;
		floatSin val_sin;
		floatSin val_cos;
		cordic360_COS_SIN_fix(angle, val_sin, val_cos,15);
		sin[0][i] = val_sin;
		cos[0][i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}
	NormalizeFirstRow:
	for (int i = 0; i < kern_size; i++) {
		sin[0][i] = sin[0][i]
				- (ap_fixed<16,3>) (sum_row_sin / (ap_fixed<16,3>) kern_size);
		cos[0][i] = cos[0][i]
				- (ap_fixed<16,3>) (sum_row_cos / (ap_fixed<16,3>) kern_size);
	}

	AssignCompleteMatrix:
	for (int i = 1; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sin[i][j] = sin[0][j];
			cos[i][j] = cos[0][j];
		}
	}

}

void generateGaborKernel_fix(int kern_size,
		floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {

	if (kern_size > MAX_KERN_SIZE)
		kern_size = MAX_KERN_SIZE;

	floatSin sin[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatSin cos[MAX_KERN_SIZE][MAX_KERN_SIZE];

	generateSinKernel_fix(kern_size, sin, cos);

	floatGauss gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	generateGaussKernel_fix(kern_size,8,gauss);

	GaussMultiSine:
	for (int i = 0; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin[i][j] * gauss[i][j];
			cos_filter_matrix[i][j] = cos[i][j] * gauss[i][j];
		}
	}
	/*
	NormalizeGausGabor: for (int i = 0; i < kern_size; i++) {
		ap_fixed<16,5> row_sum_sin = 0;
		ap_fixed<16,5> row_sum_cos = 0;
		for (int j = 0; j < kern_size; j++) {
			row_sum_sin += sin_filter_matrix[i][j];
			row_sum_cos += cos_filter_matrix[i][j];
		}
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_filter_matrix[i][j]
					- (row_sum_sin / (ap_fixed<16,5>) kern_size);
			cos_filter_matrix[i][j] = cos_filter_matrix[i][j]
					- (row_sum_cos / (ap_fixed<16,5>) kern_size);
		}
	}
*/
}

void gaborPixel_fix(int rho, int phi,
		uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH], int filter_size,
		floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		ap_uint<1> code[BITCODE_LENGTH], int pos) {
	ap_uint<9> angles = NORM_WIDTH;
	ap_fixed<15,1> total_i = 0;
	ap_fixed<15,1> total_r = 0;

	GaborPixeLoop: for (int i = 0; i < filter_size; i++) {
		ap_uint<9> image_x = i + rho - (filter_size / 2);
		for (int j = 0; j < filter_size; j++) {
			ap_uint<9> image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y, angles);
			int index = image_x * angles + image_y;
			ap_int<14> tmp = (ap_int<14>)norm_img[index];
			ap_fixed<15,1> valueS = (sin_filter_matrix[i][j])*tmp;
			ap_fixed<15,1> valueC = (cos_filter_matrix[i][j])*tmp;

			total_i = total_i + valueS; //255*6.4
			total_r = total_r + valueC;
		}
	}
	code[pos] = total_r >= 0 ? 1:0;
	code[pos+1] = total_i >= 0 ? 1:0;

	/*
	if (total_r >= 0) {
		code[pos] = 1;
	} else {
		code[pos] = 0;
	}
	if (total_i >= 0) {
		code[pos+1] = 1;
	} else {
		code[pos+1] = 0;
	}
*/
}

//template<int RESULT_W,int RESULT_H,int INTERN_W,int INTERN_H>
//compiler error for template function no function body, without template okay. Why?
void encode_fix(uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		ap_uint<1> bit_code[BITCODE_LENGTH]) {
	floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	int height = NORM_HEIGHT;
	int width = NORM_WIDTH;

	int angular_slice = NORM_WIDTH;
	int radial_slice = ENCODED_PIXELS / angular_slice;

	int max_filter = NORM_HEIGHT / 3;

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

		generateGaborKernel_fix(filter_height, sin_filter_matrix,
				cos_filter_matrix);

		int index = 0;

		CountConvLoop: for (int theta = 0; theta < angular_slice; theta++) {
			gaborPixel_fix(radius, theta, norm_img, filter_height,
					sin_filter_matrix, cos_filter_matrix, bit_code, index);
			index += 2;
		}
	}
}


/*----------------------------------------------------------------------------
 * 									MASEK
 *----------------------------------------------------------------------------
 */


void LogGaborConvole(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],int nscale, int minWaveLength, int mult){
	int width = NORM_WIDTH;
	int height = NORM_HEIGHT;
	int wavelength = minWaveLength;
	float sigmaOnf = 0.5;

	int ndata = width;
	if (ndata % 2 == 1)
		ndata -= 1;

	float radius[NORM_WIDTH/2 + 1];

	float logGabor[NORM_WIDTH];
	float filtersum[NORM_WIDTH];
	float imagefft[NORM_WIDTH];

	int tmp = ndata/2;
	radius[0] = 1;
	for (int i = 1; i<=ndata/2;i++){
		radius[i] = ((float)i*2)/tmp;
	}

	for (int s = 0; s<nscale; s++){
		float  fo = 1.0/wavelength;
		float rfo = fo/0.5;

		for (int j = 0; j<tmp+1; j++)
		{
			logGabor[j] = exp(-log(radius[j]/fo)*log(radius[j]/fo)/(2*log(sigmaOnf)*log(sigmaOnf)));
		}
		logGabor[0] = 0;
		for (int j = 0; j < ndata / 2 + 1; j++)
		{
			filtersum[j] += logGabor[j];
		}
	}

}

void createLogGaborKernel(){

}








