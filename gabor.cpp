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
		float sinK[MAX_KERN_SIZE],
		float cosK[MAX_KERN_SIZE]) {
	float sum_row_sin = 0;
	float sum_row_cos = 0;
	CalcFirstRow:
	for (int i = 0; i < kern_size; i++) {
		int phi = i - (kern_size / 2);
		int temp = kern_size / 2;
		float val_sin = sin(PI * phi / temp);
		float val_cos = cos(PI * phi / temp);

		sinK[i] = val_sin;
		cosK[i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}

	NormalizeRow:
	for (int i = 0; i < kern_size; i++) {
		float old_v_s = sinK[i];
		float old_v_c = cosK[i];
		sinK[i] = old_v_s - (sum_row_sin / (float) kern_size);
		cosK[i] = old_v_c - (sum_row_cos / (float) kern_size);
	}
}

void generateGaborKernel(int kern_size,
		float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {


	float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float sinK[MAX_KERN_SIZE];
	float cosK[MAX_KERN_SIZE];
	generateSinKernel(kern_size,sinK,cosK);
	generateGaussKernel(kern_size,8,gauss);

	GaussMulti:
	for (int i = 0; i < kern_size; i++) {
		float rho = i - (kern_size / 2);
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sinK[j] * gauss[i][j];
			cos_filter_matrix[i][j] = cosK[j] * gauss[i][j];
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

void gaborPixel(int rho, int phi, uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		int filter_size, float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],uint8_t code[BITCODE_LENGTH], int pos) {
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

	code[pos] = total_r >= 0 ? 1:0;
	code[pos+1] = total_i >= 0 ? 1:0;
}

void encode(uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		uint8_t bit_code[BITCODE_LENGTH]) {

	float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];

	int angular_slice = NORM_WIDTH;
	int radial_slice = ENCODED_PIXELS / angular_slice;
	int index = 0;

	for (int r_slice = 0; r_slice < radial_slice; r_slice++) {
		int radius = ((r_slice * (NORM_HEIGHT - 6)) / (2 * radial_slice)) + 3;
		int filter_height;

		if (radius < (NORM_HEIGHT - radius))
			filter_height = 2 * radius - 1;
		else
			filter_height = 2 * (NORM_HEIGHT - radius) - 1;

		if (filter_height > MAX_KERN_SIZE)
			filter_height = MAX_KERN_SIZE;

		generateGaborKernel(filter_height, sin_filter_matrix,
				cos_filter_matrix);

		for (int theta = 0; theta < angular_slice; theta++) {
			gaborPixel(radius, theta, norm_img, filter_height,
					sin_filter_matrix, cos_filter_matrix, bit_code, index);
			index += 2;
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
		floatSin sink[MAX_KERN_SIZE],
		floatSin cosk[MAX_KERN_SIZE]) {
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
		cordic360_COS_SIN_fix(angle, val_sin, val_cos,6);//6fuer 8bit

		sink[i] = val_sin;
		cosk[i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}
	NormalizeFirstRow:
	for (int i = 0; i < kern_size; i++) {
		/*sin[0][i] = sin[0][i]
				- (ap_fixed<16,3>) (sum_row_sin / (ap_fixed<16,3>) kern_size);
		cos[0][i] = cos[0][i]
				- (ap_fixed<16,3>) (sum_row_cos / (ap_fixed<16,3>) kern_size);
				*/
		sink[i] = sink[i]-(floatSin)((float)sum_row_sin / (float) kern_size);
		cosk[i] = cosk[i]-(floatSin)((float)sum_row_cos / (float) kern_size);
	}
}

void generateGaborKernel_fix(int kern_size,
		floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {

	floatSin sin_k[MAX_KERN_SIZE];
	floatSin cos_k[MAX_KERN_SIZE];

	generateSinKernel_fix(kern_size, sin_k, cos_k);

	floatGauss gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	generateGaussKernel_fix(kern_size,15,gauss);

	GaussMultiSine:
	for (int i = 0; i < kern_size; i++) {
		for (int j = 0; j < kern_size; j++) {
			sin_filter_matrix[i][j] = sin_k[j] * gauss[i][j];
			cos_filter_matrix[i][j] = cos_k[j] * gauss[i][j];
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
		ap_uint<2> code[BITCODE_LENGTH], int pos) {
	ap_uint<9> angles = NORM_WIDTH;
	ap_fixed<15,14> total_i = 0;
	ap_fixed<15,14> total_r = 0;

	GaborPixeLoop: for (int i = 0; i < filter_size; i++) {
		ap_uint<9> image_x = i + rho - (filter_size / 2);
		for (int j = 0; j < filter_size; j++) {
			ap_uint<9> image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y, angles);
			int index = image_x * angles + image_y;
			ap_uint<8> tmp = (ap_uint<8>)norm_img[index];
			ap_fixed<15,14> valueS = (sin_filter_matrix[i][j]*tmp);
			ap_fixed<15,14> valueC = (cos_filter_matrix[i][j]*tmp);


			total_i = total_i + valueS; //255*6.4
			total_r = total_r + valueC;
			//std::cout << total_i.to_float() <<"\n";
		}
	}
	code[pos] = total_r >= 0 ? 1:0;
	code[pos+1] = total_i >= 0 ? 1:0;
}

void encode_fix(uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		ap_uint<2> bit_code[BITCODE_LENGTH]) {

	floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];

	int angular_slice = NORM_WIDTH;
	int radial_slice = ENCODED_PIXELS / angular_slice;
	int index = 0;
	for (int r_slice = 0; r_slice < radial_slice; r_slice++) {
		int radius = ((r_slice * (NORM_HEIGHT - 6)) / (2 * radial_slice)) + 3;
		int filter_height;

		filter_height = radius < (NORM_HEIGHT - radius)? 2 * radius - 1:filter_height = 2 * (NORM_HEIGHT - radius) - 1;

		if (filter_height > MAX_KERN_SIZE) filter_height = MAX_KERN_SIZE;

		generateGaborKernel_fix(filter_height, sin_filter_matrix,
				cos_filter_matrix);

		CountConvLoop: for (int theta = 0; theta < angular_slice; theta++) {
			gaborPixel_fix(radius, theta, norm_img, filter_height,
					sin_filter_matrix, cos_filter_matrix, bit_code, index);
			index += 2;
		}
	}
}


int gaborPixel_visual(int rho, int phi, uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
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
	int ret =0;
	if(total_r>=0){
		if(total_i>=0){
			ret = 3;
		}else{
			ret = 2;
		}
	}else{
		if(total_i>=0){
			ret = 1;
		}else{
			ret = 0;
		}
	}
	return ret;
}

int gaborPixel_visual_fix(int rho, int phi, uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		int filter_size, floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]) {

	ap_uint<9> angles = NORM_WIDTH;
	ap_fixed<15,14> total_i = 0;
	ap_fixed<15,14> total_r = 0;
	GaborPixeLoop:
	for (int i = 0; i < filter_size; i++) {
		ap_uint<9> image_x = i + rho - (filter_size / 2);
		for (int j = 0; j < filter_size; j++) {
			ap_uint<9> image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y, angles);
			int index = image_x * angles + image_y;
			ap_uint<8> tmp = (ap_uint<8>)norm_img[index];
			ap_fixed<15,14> valueS = (sin_filter_matrix[i][j]*tmp);
			ap_fixed<15,14> valueC = (cos_filter_matrix[i][j]*tmp);


			total_i = total_i + valueS; //255*6.4
			total_r = total_r + valueC;
			//std::cout << total_i.to_float() <<"\n";
		}
	}
	int ret =0;
	if(total_r>=0){
		if(total_i>=0){
			ret = 3;
		}else{
			ret = 2;
		}
	}else{
		if(total_i>=0){
			ret = 1;
		}else{
			ret = 0;
		}
	}
	return ret;
}

void visualize_float(uint8_t norm_img[32*360],NORM_RGB_IMAGE &out){
	int radii  = 32;
	int angels = 360;
	int filter_size = 9;

	float gaborR[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float gaborI[MAX_KERN_SIZE][MAX_KERN_SIZE];


	generateGaborKernel(filter_size,gaborI,gaborR);

	RGBPIXEL px;
	for (int i = 0;i<radii;i++){
		for(int j = 0;j<angels;j++){
			if ((i<=filter_size/2) or (i>=(radii-(filter_size/2)))){
				px.val[0] = 0;
				px.val[1] = 0;
				px.val[2] = 0;
				out << px;
			}else{
				int temp = gaborPixel_visual(i,j,norm_img,filter_size,gaborI,gaborR );
				int real = (temp & 2)>>1;
				int imag =  temp & 1;
				if (imag == 1){
					if (real==1){
						px.val[0] = 255;
						px.val[1] = 0;
						px.val[2] = 0;
						out << px;
					}else{
						px.val[0] = 0;
						px.val[1] = 255;
						px.val[2] = 0;
						out << px;
					}
				}else{
					if (real==1){
						px.val[0] = 0;
						px.val[1] = 0;
						px.val[2] = 255;
						out << px;
					}else{
						px.val[0] = 0;
						px.val[1] = 255;
						px.val[2] = 255;
						out << px;
					}
				}
			}
		}
	}

}

void visualize_fix(uint8_t norm_img[32*360],NORM_RGB_IMAGE &out){
	int radii  = 32;
	int angels = 360;
	int filter_size = 9;

	floatGabor gaborRf[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatGabor gaborIf[MAX_KERN_SIZE][MAX_KERN_SIZE];


	generateGaborKernel_fix(filter_size,gaborIf,gaborRf);


	RGBPIXEL px;
	for (int i = 0;i<radii;i++){
		for(int j = 0;j<angels;j++){
			if ((i<=filter_size/2) or (i>=(radii-(filter_size/2)))){
				px.val[0] = 0;
				px.val[1] = 0;
				px.val[2] = 0;
				out << px;
			}else{
				int temp = gaborPixel_visual_fix(i,j,norm_img,filter_size,gaborIf,gaborRf );
				int real = (temp & 2)>>1;
				int imag =  temp & 1;
				if (imag == 1){
					if (real==1){
						px.val[0] = 255;
						px.val[1] = 0;
						px.val[2] = 0;
						out << px;
					}else{
						px.val[0] = 0;
						px.val[1] = 255;
						px.val[2] = 0;
						out << px;
					}
				}else{
					if (real==1){
						px.val[0] = 0;
						px.val[1] = 0;
						px.val[2] = 255;
						out << px;
					}else{
						px.val[0] = 0;
						px.val[1] = 255;
						px.val[2] = 255;
						out << px;
					}
				}
			}
		}
	}

}

//------------------------------------------------------------------------------------
//					Gabor Kernel Fix Point without calc matrix
//					based on normalized image size of 32x360
//					only 2 matrix are needed, so save/burn then on hardware
//					GAuss peak = 8
//-----------------------------------------------------------------------------------
/*
static floatGabor gaborKernel_5_imag[MAX_KERN_SIZE][MAX_KERN_SIZE]={
		{0,-0.774831,0,1.342047,-0,0,0,0,0,0},
		{0,-2.324494,0,4.026142,-0,0,0,0,0,0},
		{0,-4.026142,0,6.973484,-0,0,0,0,0,0},
		{0,-4.026142,0,6.973484,-0,0,0,0,0,0},
		{0,-2.324494,0,4.026142,-0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
};
static floatGabor gaborKernel_5_real[MAX_KERN_SIZE][MAX_KERN_SIZE]  ={
		{-0.206622,0.154966,1.610456,0.268409,-0.619865,0,0,0,0,0},
		{-0.619865,0.464899,4.831371,0.805228,-1.859595,0,0,0,0,0},
		{-1.073638,0.805228,8.368181,1.394696,-3.220914,0,0,0,0,0},
		{-1.073638,0.805228,8.368181,1.394696,-3.220914,0,0,0,0,0},
		{-0.619865,0.464899,4.831371,0.805228,-1.859595,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
};
static floatGabor gaborKernel_10_imag[MAX_KERN_SIZE][MAX_KERN_SIZE]  ={
		{0,-0.508493,-1.202828,-1.577653,-1.147383,0,1.147383,1.577653,1.202828,0.508493},
		{0,-0.828589,-1.960007,-2.570783,-1.869659,0,1.869659,2.570783,1.960007,0.828589},
		{0,-1.211351,-2.865421,-3.758341,-2.733337,0,2.733337,3.758341,2.865421,1.211351},
		{0,-1.588831,-3.758341,-4.929512,-3.585097,0,3.585097,4.929512,3.758341,1.588831},
		{0,-1.869658,-4.422632,-5.800809,-4.218767,0,4.218767,5.800809,4.422632,1.869658},
		{0,-1.973894,-4.669199,-6.124211,-4.453969,0,4.453969,6.124211,4.669199,1.973894},
		{0,-1.869658,-4.422632,-5.800809,-4.218767,0,4.218767,5.800809,4.422632,1.869658},
		{0,-1.588831,-3.758341,-4.929512,-3.585097,0,3.585097,4.929512,3.758341,1.588831},
		{0,-1.211351,-2.865421,-3.758341,-2.733337,0,2.733337,3.758341,2.865421,1.211351},
		{0,-0.828589,-1.960007,-2.570783,-1.869659,0,1.869659,2.570783,1.960007,0.828589}
};
static floatGabor gaborKernel_10_real[MAX_KERN_SIZE][MAX_KERN_SIZE]  ={
		{-0.530900,-0.699881,-0.390823,0.512610,1.579237,2.060873,1.579237,0.512610,-0.390823,-0.699881},
		{-0.865100,-1.140455,-0.636845,0.835298,2.573365,3.358190,2.573365,0.835298,-0.636845,-1.140455},
		{-1.264728,-1.667281,-0.931032,1.221159,3.762116,4.909486,3.762116,1.221159,-0.931032,-1.667281},
		{-1.658842,-2.186838,-1.221159,1.601696,4.934464,6.439376,4.934464,1.601696,-1.221159,-2.186838},
		{-1.952045,-2.573364,-1.437000,1.884797,5.806636,7.577544,5.806636,1.884797,-1.437000,-2.573364},
		{-2.060873,-2.716832,-1.517115,1.989877,6.130362,8.000000,6.130362,1.989877,-1.517115,-2.716832},
		{-1.952045,-2.573364,-1.437000,1.884797,5.806636,7.577544,5.806636,1.884797,-1.437000,-2.573364},
		{-1.658842,-2.186838,-1.221159,1.601696,4.934464,6.439376,4.934464,1.601696,-1.221159,-2.186838},
		{-1.264728,-1.667281,-0.931032,1.221159,3.762116,4.909486,3.762116,1.221159,-0.931032,-1.667281},
		{-0.865100,-1.140455,-0.636845,0.835298,2.573365,3.358190,2.573365,0.835298,-0.636845,-1.140455}
};
void encode_fix_fast(uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		ap_uint<2> bit_code[BITCODE_LENGTH]) {

	floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
	int height = NORM_HEIGHT;
	int width = NORM_WIDTH;

	int angular_slice = NORM_WIDTH;
	int radial_slice = ENCODED_PIXELS / angular_slice;
	int index = 0;
	for (int r_slice = 0; r_slice < radial_slice; r_slice++) {
		int radius = ((r_slice * (height - 6)) / (2 * radial_slice)) + 3;
		int filter_height;

		if (radius < (height - radius)) {
			filter_height = 2 * radius - 1;
		} else {
			filter_height = 2 * (height - radius) - 1;
		}
		if (filter_height > MAX_KERN_SIZE)
			filter_height = MAX_KERN_SIZE;

		if (filter_height == 5) {
			sin_filter_matrix = gaborKernel_5_imag;
			cos_filter_matrix = gaborKernel_5_real;
		} else {
			if (filter_height == 10) {
				sin_filter_matrix = gaborKernel_10_imag;
				cos_filter_matrix = gaborKernel_10_real;
			} else {
				generateGaborKernel_fix(filter_height, sin_filter_matrix,
						cos_filter_matrix);
			}
		}

		CountConvLoop: for (int theta = 0; theta < angular_slice; theta++) {
			gaborPixel_fix(radius, theta, norm_img, filter_height,
					sin_filter_matrix, cos_filter_matrix, bit_code, index);
			index += 2;
		}
	}
}
*/

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








