#include "toplevel.hpp"

float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];
float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE];

float sin_filter_matrix_fix[MAX_KERN_SIZE][MAX_KERN_SIZE];
float cos_filter_matrix_fix[MAX_KERN_SIZE][MAX_KERN_SIZE];

//uint8_t bit_code[BITCODE_LENGTH];
//ap_uint<BITCODE_LENGTH> bitcode_t;

void findPupil(GRAY_IMAGE& img, int& r, int& x, int& y,GRAY_IMAGE &dst_img){
	PIXELGRAY pixel_value;
	int startX_line = 0;
	int length_line = 0;
	int gap_count  = 0;//how many pixel are between
	const int max_gap = 5;//10;//if more pixel are between this and a further black pixel the line is ending
	int longest_line_in_row		= 0;
	int start_longest_lineX 	= 0;

	bool is_line = false;

	int total_longest_line = 0;
 	int total_y = 0;
 	int total_x = 0;


	loopPixel:
	for (int y=0;y<MAX_HEIGHT_CASIA;y++){
		for (int x=0;x<MAX_WIDTH_CASIA;x++){
			#pragma HLS loop_flatten off
			#pragma HLS pipeline II=1
			img >> pixel_value;
			dst_img <<pixel_value;
			if (pixel_value.val[0]<=70){
				//pixel is black
				if (!is_line){
					startX_line  = x;
					length_line  = 1;
					is_line = true;
				}else{
					length_line += 1;
				}
				gap_count = 0;
			}else{
				//pixel is not black,the white noise in pupil
				if (is_line){
					gap_count +=1;
					length_line += 1;
					if (gap_count >= max_gap){
						//noise are to big, line is ending
						length_line -= max_gap;
						is_line = false;
						gap_count = 0;
						if (length_line > longest_line_in_row){
							longest_line_in_row = length_line;
							length_line  = 0;
							start_longest_lineX = startX_line;
							if (longest_line_in_row > total_longest_line){
								total_longest_line = longest_line_in_row;
								total_x = startX_line;
								total_y = y;
							}

						}
					}
				}
			}
		}
	}


	r = (int)total_longest_line/2;
	x = total_x+r;
	y = total_y;
}

void findPupil2(GRAY_IMAGE& img, int& r, int& x, int& y,GRAY_IMAGE &dst_img){
	PIXELGRAY pixel_value;
	int startX_line = 0;
	int length_line = 0;
	int gap_count  = 0;//how many pixel are between
	const int max_gap = 10;//10;//if more pixel are between this and a further black pixel the line is ending
	int longest_line_in_row		= 0;
	int start_longest_lineX 	= 0;

	bool is_line = false;

	int total_longest_line = 0;
 	int total_y = 0;
 	int total_x = 0;

	int startSearchingAreaX = 75;//MAX_WIDTH/4,26MAX_WIDTH/6;
	int startSearchingAreaY = 75;//MAX_HEIGHT/3,73MAX_HEIGHT/6;
	int endSearchingAreaX   = 250;//MAX_WIDTH  - MAX_WIDTH/6;
	int endSearchingAreaY   = 250;//MAX_HEIGHT - MAX_HEIGHT/6;



	loopPixel:
	for (int y=0;y<MAX_HEIGHT_CASIA;y++){
		for (int x=0;x<MAX_WIDTH_CASIA;x++){
			#pragma HLS loop_flatten off
			#pragma HLS pipeline II=1
			img >> pixel_value;
			dst_img <<pixel_value;

			if (y>startSearchingAreaY && y< endSearchingAreaY){
				if(x>startSearchingAreaX && x < endSearchingAreaX){
					if (pixel_value.val[0]<=70){
						//pixel is black
						if (!is_line){
							startX_line  = x;
							length_line  = 1;
							is_line = true;
						}else{
							length_line += 1;
						}
						gap_count = 0;
					}else{
						//pixel is not black,the white noise in pupil
						if (is_line){
							gap_count +=1;
							length_line += 1;
							if (gap_count >= max_gap){
								//noise are to big, line is ending
								length_line -= max_gap;
								is_line = false;
								gap_count = 0;

								if (length_line > longest_line_in_row){
									longest_line_in_row = length_line;
									length_line  = 0;
									start_longest_lineX = startX_line;

									if (longest_line_in_row > total_longest_line){
										total_longest_line = longest_line_in_row;
										total_x = startX_line;
										total_y = y;
									}
								}
							}
						}
					}
				}
			}
		}
	}


	r = (int)total_longest_line/2;
	x = total_x+r;
	y = total_y;
}

void improve(GRAY_IMAGE& img, int& r_estimate, int& x_estimate, int& y_estimate,GRAY_IMAGE &dst_img){
	//					45		135		225		   315
	float angleList[8] = {0.7,0.7,-0.7,0.7,-0.7,-0.7,0.7,-0.7};
	//x range * y range * points on circle * radii
	int neededValues[10*10*8*3];//2400
	int sums[3*10*10];
	int j = 0;
	for (int x = x_estimate-5; x < x_estimate+5; x++)
	{
		for (int y = y_estimate-5; y < y_estimate+5; x++)
		{
			for (int r = r_estimate;r<=r_estimate+3;r++){
				for(int i=0;i<8;i+=2){
					neededValues[j] = x + r*angleList[i];
					neededValues[j+1] = y + r*angleList[i+1];
					j += 2;
				}

			}
		}
	}
	PIXELGRAY pixel;
	loopPixel:
	for (int y=0;y<MAX_HEIGHT_CASIA;y++){
		for (int x=0;x<MAX_WIDTH_CASIA;x++){
			#pragma HLS loop_flatten off
			#pragma HLS pipeline II=1
			img >> pixel;
			dst_img <<pixel;
			for (int i=0;i<2400;i+=2){
				if (neededValues[i]==x and neededValues[i+1]==y){
					int pos = (int) i/4;
					sums[pos] +=  pixel.val[0];
				}
			}
		}
	}

	int i_max 		= 0;
	int iris_radius = 0;
	int sum1 = 0;
	int sum2 = 0;
	int nr = 0;
	for (int r= 1;r<300;r++){
		sum1 = sums[r+1];
		sum2 = sums[r-1];
		int diff = sum1 - sum2;
		if (diff > i_max){
			i_max = diff;
			iris_radius = r;//bester kreis ist nummer r von der ersten schleife
			nr = r;
		}
	}
}

void find_iris_high_accuracy(GRAY_IMAGE& img, int& pupilRadius, int& x, int& y,int& irisRadius,GRAY_IMAGE &dst_img){
	int i_max 		= 0;
	int iris_radius = 0;

	//int points[IRIS_RADIUS_MAX - IRIS_RADIUS_MIN + 2][6][3];//iris raius max - min 6 punkte 0,45,... x/y
	int points[(IRIS_RADIUS_MAX - IRIS_RADIUS_MIN + 2)*6*2];//37 radien jeweils mit 6 punkten mit x und y
	int count1 = 0;
	int count2 = 0;
	//calc points we have compute
	for (int r =IRIS_RADIUS_MIN-1; r<IRIS_RADIUS_MAX+1;r++ ){
		count2 = 0;
		for (int alpha = 0; alpha <360;alpha+=45){
			float sinus 	=  replaceSIN(alpha);
			float cosinus 	=  replaceCOS(alpha);
			int cx = x + r * cosinus;
			int cy = y + r * sinus;
			points[count1*12+count2*2+0] = cx;
			points[count1*12+count2*2+1] = cy;
			count2++;
		}
		count1++;
	}

	PIXELGRAY pixel_value;
	int sums[37];//37*6*2/12=737 summen aller kreise
	for (int i=0;i<37;i++)sums[i]=0;
	int count =0;
	loopPixel:
	for (int y=0;y<MAX_HEIGHT_CASIA;y++){
		for (int x=0;x<MAX_WIDTH_CASIA;x++){
			//#pragma HLS loop_flatten off
			//#pragma HLS pipeline II=1
			img >> pixel_value;
			dst_img << pixel_value;
			for (int p = 0;p<444;p+=2){
				if (points[p]==x and points[p+1]==y){
					int pos = (int) p/12;
					sums[pos] +=  pixel_value.val[0];
				}
			}
		}
	}
	int sum1 = 0;
	int sum2 = 0;
	for (int r= 1;r<37;r++){
		sum1 = sums[r+1];
		sum2 = sums[r-1];
		int diff = sum1 - sum2;
		if (diff > i_max){
			i_max = diff;
			iris_radius = r;//bester kreis ist nummer r von der ersten schleife
		}
	}

	irisRadius = IRIS_RADIUS_MIN + iris_radius;
}

void find_iris_low_accuracy(GRAY_IMAGE& img, int& pupilRadius, int& x, int& y,int& irisRadius,GRAY_IMAGE &dst_img){
	int i_max 		= 0;
	int iris_radius = 0;

	//int points[IRIS_RADIUS_MAX - IRIS_RADIUS_MIN + 2][6][3];//iris raius max - min 6 punkte 0,45,... x/y
	int points[37*6*2];//37 radien jeweils mit 6 punkten mit x und y
	int count1 = 0;
	int count2 = 0;
	//calc points we have compute
	for (int r =IRIS_RADIUS_MIN-1; r<IRIS_RADIUS_MAX+1;r++ ){
		count2 = 0;
		for (int alpha = 0; alpha <360;alpha+=45){
			if (alpha != 90 and alpha != 270){
				int cx = x + r * replaceCOS(alpha);
				int cy = y + r * replaceSIN(alpha);
				points[count1*12+count2*2+0] = cx;
				points[count1*12+count2*2+1] = cy;
				count2++;
			}

		}
		count1++;
	}

	PIXELGRAY pixel_value;
	int sums[37];//37*6*2/12=737 summen aller kreise
	for (int i=0;i<37;i++)sums[i]=0;
	int count =0;
	loopPixel:
	for (int y=0;y<MAX_HEIGHT_CASIA;y++){
		for (int x=0;x<MAX_WIDTH_CASIA;x++){
			//#pragma HLS loop_flatten off
			//#pragma HLS pipeline II=1
			img >> pixel_value;
			dst_img << pixel_value;
			for (int p = 0;p<444;p+=2){
				if (points[p]==x and points[p+1]==y){
					int pos = (int) p/12;
					sums[pos] +=  pixel_value.val[0];
				}
			}
		}
	}
	int sum1 = 0;
	int sum2 = 0;
	for (int r= 1;r<37;r++){
		sum1 = sums[r+1];
		sum2 = sums[r-1];
		int diff = sum1 - sum2;
		if (diff > i_max){
			i_max = diff;
			iris_radius = r;//bester kreis ist nummer r von der ersten schleife
		}
	}

		irisRadius = IRIS_RADIUS_MIN + iris_radius;
}

void core_high(unsigned char image_in[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA],unsigned char image_out[NORM_HEIGHT*NORM_WIDTH],int values[6]){
	int x_p=values[0];
	int y_p=values[1];
	int r_p=values[2];
	int r_i=values[3];

	int rows = MAX_HEIGHT_CASIA;
	int cols = MAX_WIDTH_CASIA;

	for(int theta = 0; theta < NORM_WIDTH; theta++){
		float thetaDot = theta*DEGtoRAD;
		float temp1,temp2,temp3,temp4;
		float tempSin,tempCos;

		tempSin = sin(thetaDot);
		tempCos = cos(thetaDot);//hls::
		temp1 =(float) (x_p+r_p*tempCos);
		temp2 =(float) (x_p+r_i*tempCos);
		temp3 =(float) (y_p+r_p*tempSin);
		temp4 =(float) (y_p+r_i*tempSin);

	    for(int r = 0; r < NORM_HEIGHT; r++){
	    	float radius = r/((float)NORM_HEIGHT);

			int x = int((1-radius)*temp1 + radius*temp2);
			int y = int((1-radius)*temp3 + radius*temp4);

			image_out[r*NORM_WIDTH+theta] = image_in[y*MAX_WIDTH_CASIA+x];
	    }
	}
}

void core_low(unsigned char image_in[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA],unsigned char image_out[NORM_HEIGHT*NORM_WIDTH],int values[6]){
	int x_p=values[0];
	int y_p=values[1];
	int r_p=values[2];
	int r_i=values[3];

	int rows = MAX_HEIGHT_CASIA;
	int cols = MAX_WIDTH_CASIA;

	for(int theta = 0; theta < NORM_WIDTH; theta++){
		//float thetaDot = theta*DEGtoRAD;
		float temp1,temp2,temp3,temp4;
		float tempSin,tempCos;

		tempCos = cordic360_Cos_fixed(theta*DEGtoRAD,10).to_float();
		tempSin = cordic360_Sin_fixed(theta*DEGtoRAD,10).to_float();

		temp1 =(float) (x_p+r_p*tempCos);
		temp2 =(float) (x_p+r_i*tempCos);
		temp3 =(float) (y_p+r_p*tempSin);
		temp4 =(float) (y_p+r_i*tempSin);

	    for(int r = 0; r < NORM_HEIGHT; r++){
	    	float radius = r/((float)NORM_HEIGHT);

			int x = int((1-radius)*temp1 + radius*temp2);
			int y = int((1-radius)*temp3 + radius*temp4);

			image_out[r*NORM_WIDTH+theta] = image_in[y*MAX_WIDTH_CASIA+x];
	    }
	}
}

//------------------------------------------------------------------
// 							GABOR FILTER
//------------------------------------------------------------------


int MODULO(int a,int b){
	//negative mod is not defined very well
	int res = a % b;
	return res < 0 ? res + b: res;
}

void generateGaborKernel(int kern_size){
	float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	if (kern_size>MAX_KERN_SIZE) kern_size = MAX_KERN_SIZE;

	float sum_row_sin = 0;
	float sum_row_cos = 0;
	CalcFirstRow:for (int i = 0;i<kern_size;i++){
		int phi = i - (kern_size / 2);
		int temp = kern_size/2;
		float val_sin = (float) cordic360_Sin_fixed(PI * phi / temp,10);
		float val_cos = (float) cordic360_Cos_fixed(PI * phi / temp,10 );
		sin_filter_matrix[0][i] = val_sin;
		cos_filter_matrix[0][i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}

	NormalizeFirstRow:for (int i = 0;i<kern_size;i++){
		float old_v_s = sin_filter_matrix[0][i];
		float old_v_c = cos_filter_matrix[0][i];
		sin_filter_matrix[0][i] = old_v_s - (sum_row_sin/(float)kern_size);
		cos_filter_matrix[0][i] = old_v_c - (sum_row_cos/(float)kern_size);
	}

	AssignCompleteMatrix:for (int i = 1;i<kern_size;i++){
		for (int j = 0;j<kern_size;j++){
			sin_filter_matrix[i][j] = sin_filter_matrix[0][j];
			cos_filter_matrix[i][j] = cos_filter_matrix[0][j];
		}
	}
	int peak = 15;
	float alpha = (kern_size - 1) * 0.4770322291;
	float alphaPower = alpha * alpha;
	CreateGauss:for (int i = 0; i<kern_size; i++){
		float rho =  i - ((float)kern_size / 2.0);
		float rhoPower2 = rho*rho;
		CreateGaussInner:for(int j = 0; j<kern_size; j++){
			float phi = j - ((float)kern_size / 2.0);
			//float temp = (float)(peak * exp(-pow(rho,2)/pow(alpha,2)) * exp(-pow(phi,2)/pow(alpha,2)));//bzw exp1 alpha exp2 beta
			//float temp = (float)(peak * exp(-(rho*rho))/(alpha*alpha) * exp(-(phi*phi)/(alpha*alpha)));

			float temp1 = -(rhoPower2+phi*phi)/alphaPower;
			float temp  = peak * hls::expf(temp1);//expf(temp1);
			gauss[i][j] = temp;
		}
	}
	GaussMulti:for (int i = 0; i<kern_size; i++){
			float rho =  i - (kern_size / 2);
			for(int j = 0; j<kern_size; j++){
				float temp_sin = sin_filter_matrix[i][j] * gauss[i][j];
				float temp_cos = cos_filter_matrix[i][j] * gauss[i][j];
				sin_filter_matrix[i][j] = temp_sin;
				cos_filter_matrix[i][j] = temp_cos;
			}
		}

	NormalizeGausGabor:
	for(int i = 0 ; i < kern_size; i++ ){
		float row_sum_sin = 0;
		float row_sum_cos = 0;
			for (int j = 0 ; j<kern_size; j++){
				row_sum_sin += sin_filter_matrix[i][j];
				row_sum_cos += cos_filter_matrix[i][j];
			}
			for (int j = 0 ; j<kern_size; j++){
				float old_sin = sin_filter_matrix[i][j];
				float old_cos = cos_filter_matrix[i][j];
				sin_filter_matrix[i][j] = old_sin - (row_sum_sin/(float)kern_size);
				cos_filter_matrix[i][j] = old_cos - (row_sum_cos/(float)kern_size);
			}
		}

}


uint8_t gaborPixel(int rho, int phi, uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],int filter_size){
	int angles = NORM_WIDTH;
	float total_i = 0.0;
	float total_r = 0.0;

	GaborPixeLoop:
	for (int i = 0; i<filter_size;i++){
		for (int j = 0; j<filter_size;j++){
			int image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y,angles);

			int image_x =  i + rho - (filter_size / 2);
			int tmp = norm_img[image_x*NORM_WIDTH+image_y];
			total_i += sin_filter_matrix[i][j] * tmp;
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

void encode(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],uint8_t bit_code[BITCODE_LENGTH]){
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

		generateGaborKernel(filter_height);

		for (int theta = 0;theta<angular_slice;theta++){
			uint8_t temp = gaborPixel(radius,theta,norm_img,filter_height);
			bit_code[index]   = (temp & 2)>>1;//real
			bit_code[index+1] = temp & 1;//imag
			index+=2;
		}
	}
}



void generateGaborKernel_fix(int kern_size){
	float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	if (kern_size>MAX_KERN_SIZE) kern_size = MAX_KERN_SIZE;

	float sum_row_sin = 0;
	float sum_row_cos = 0;
	CalcFirstRow:for (int i = 0;i<kern_size;i++){
		int phi = i - (kern_size / 2);
		int temp = kern_size/2;
		float val_sin = cordic360_SIN(PI * phi / temp,5);
		float val_cos = cordic360_COS(PI * phi / temp,5 );
		sin_filter_matrix_fix[0][i] = val_sin;
		cos_filter_matrix_fix[0][i] = val_cos;
		sum_row_sin += val_sin;
		sum_row_cos += val_cos;
	}

	NormalizeFirstRow:for (int i = 0;i<kern_size;i++){
		float old_v_s = sin_filter_matrix_fix[0][i];
		float old_v_c = cos_filter_matrix_fix[0][i];
		sin_filter_matrix_fix[0][i] = old_v_s - (sum_row_sin/(float)kern_size);
		cos_filter_matrix_fix[0][i] = old_v_c - (sum_row_cos/(float)kern_size);
	}

	AssignCompleteMatrix:for (int i = 1;i<kern_size;i++){
		for (int j = 0;j<kern_size;j++){
			sin_filter_matrix_fix[i][j] = sin_filter_matrix_fix[0][j];
			cos_filter_matrix_fix[i][j] = cos_filter_matrix_fix[0][j];
		}
	}
	int peak = 15;
	float alpha = (kern_size - 1) * 0.4770322291;
	float alphaPower = alpha * alpha;
	CreateGauss:for (int i = 0; i<kern_size; i++){
		float rho =  i - ((float)kern_size / 2.0);
		float rhoPower2 = rho*rho;
		CreateGaussInner:for(int j = 0; j<kern_size; j++){
			float phi = j - ((float)kern_size / 2.0);
			//float temp = (float)(peak * exp(-pow(rho,2)/pow(alpha,2)) * exp(-pow(phi,2)/pow(alpha,2)));//bzw exp1 alpha exp2 beta
			//float temp = (float)(peak * exp(-(rho*rho))/(alpha*alpha) * exp(-(phi*phi)/(alpha*alpha)));

			float temp1 = -(rhoPower2+phi*phi)/alphaPower;
			float temp  = peak * hls::expf(temp1);//expf(temp1);
			gauss[i][j] = temp;
		}
	}
	GaussMulti:for (int i = 0; i<kern_size; i++){
			float rho =  i - (kern_size / 2);
			for(int j = 0; j<kern_size; j++){
				float temp_sin = sin_filter_matrix_fix[i][j] * gauss[i][j];
				float temp_cos = cos_filter_matrix_fix[i][j] * gauss[i][j];
				sin_filter_matrix_fix[i][j] = temp_sin;
				cos_filter_matrix_fix[i][j] = temp_cos;
			}
		}

	NormalizeGausGabor:
	for(int i = 0 ; i < kern_size; i++ ){
		float row_sum_sin = 0;
		float row_sum_cos = 0;
			for (int j = 0 ; j<kern_size; j++){
				row_sum_sin += sin_filter_matrix_fix[i][j];
				row_sum_cos += cos_filter_matrix_fix[i][j];
			}
			for (int j = 0 ; j<kern_size; j++){
				float old_sin = sin_filter_matrix_fix[i][j];
				float old_cos = cos_filter_matrix_fix[i][j];
				sin_filter_matrix_fix[i][j] = old_sin - (row_sum_sin/(float)kern_size);
				cos_filter_matrix_fix[i][j] = old_cos - (row_sum_cos/(float)kern_size);
			}
		}

}


uint8_t gaborPixel_fix(int rho, int phi, uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],int filter_size){
	int angles = NORM_WIDTH;
	float total_i = 0.0;
	float total_r = 0.0;

	GaborPixeLoop:
	for (int i = 0; i<filter_size;i++){
		for (int j = 0; j<filter_size;j++){
			int image_y = j + phi - (filter_size / 2);
			image_y = MODULO(image_y,angles);

			int image_x =  i + rho - (filter_size / 2);
			int tmp = norm_img[image_x*NORM_WIDTH+image_y];
			total_i += sin_filter_matrix_fix[i][j] * tmp;
			total_r += cos_filter_matrix_fix[i][j] * tmp;
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

void encode_fix(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],uint8_t bit_code[BITCODE_LENGTH]){
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

		generateGaborKernel_fix(filter_height);

		for (int theta = 0;theta<angular_slice;theta++){
			uint8_t temp = gaborPixel_fix(radius,theta,norm_img,filter_height);
			bit_code[index]   = (temp & 2)>>1;//real
			bit_code[index+1] = temp & 1;//imag
			index+=2;
		}
	}
}

//-------------------------------------------------------------
//							Top call methods
//-------------------------------------------------------------
void writeValues(int values[6],int x, int y,int r1, int r2){
	values[0] = x;
	values[1] = y;
	values[2] = r1;
	values[3] = r2;
}
void arrayMethod_fix(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]){
	RGB_IMAGE  img0(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img1(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img2(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img3(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);
	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};

	uint8_t imageIn[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH_CASIA>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	core_low(imageIn,imageOut,val);
	encode_fix(imageOut,code);
	//code = bit_code;

}

void arrayMethod(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]){
	RGB_IMAGE  img0(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img1(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img2(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img3(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);
	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};

	uint8_t imageIn[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH_CASIA>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	core_low(imageIn,imageOut,val);
	encode(imageOut,code);
	//code = bit_code;

}


void arrayMethodschnell(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]){
	NORM_RGB_IMAGE  img0(NORM_HEIGHT, NORM_WIDTH);
	NORM_GRAY_IMAGE img1(NORM_HEIGHT, NORM_WIDTH);

	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};

	uint8_t imageIn[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	hls::Mat2Array<NORM_WIDTH>(img1, imageOut);
	encode(imageOut,code);
	//code = bit_code;

}


void method1(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img1(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img2(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img3(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	unsigned char imageIn[MAX_WIDTH_CASIA*MAX_HEIGHT_CASIA];
	unsigned char imageOut[NORM_HEIGHT*NORM_WIDTH];

	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH_CASIA>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	core_low(imageIn,imageOut,val);
	hls::Array2Mat<NORM_WIDTH>(imageOut, img4);
	hls::CvtColor<HLS_GRAY2RGB>(img4, img5);
	hls::Mat2AXIvideo(img5, outputStream);

}

void method2(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img1(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img2(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img3(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	RGB_IMAGE  img4(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);

	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);

}

void top_level(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE axis port=outputStream
#pragma HLS INTERFACE ap_ctrl_none port=return

	method1(inputStream,outputStream);
}

void test_detection_top(AXI_STREAM& inputStream,int& x,int& y, int& r1, int& r2){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=y
#pragma HLS INTERFACE s_axilite port=r1
#pragma HLS INTERFACE s_axilite port=r2
#pragma HLS INTERFACE ap_ctrl_none port=return

	RGB_IMAGE  img0(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img1(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img2(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);
	GRAY_IMAGE img3(MAX_HEIGHT_CASIA, MAX_WIDTH_CASIA);

#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);

}
