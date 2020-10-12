#include "normalization.hpp"

void norm_high(uint8_t image_in[MAX_HEIGHT_CASIA * MAX_WIDTH_CASIA],
		uint8_t image_out[NORM_HEIGHT * NORM_WIDTH], int values[6]) {
	int x_p = values[0];
	int y_p = values[1];
	int r_p = values[2];
	int r_i = values[3];

	for (int theta = 0; theta < NORM_WIDTH; theta++) {
		float thetaDot = theta * DEGtoRAD;
		float temp1, temp2, temp3, temp4;
		float tempSin, tempCos;

		tempSin = sin(thetaDot);
		tempCos = cos(thetaDot);
		temp1 = (float) (x_p + r_p * tempCos);
		temp2 = (float) (x_p + r_i * tempCos);
		temp3 = (float) (y_p + r_p * tempSin);
		temp4 = (float) (y_p + r_i * tempSin);

		for (int r = 0; r < NORM_HEIGHT; r++) {
			float radius = r / ((float) NORM_HEIGHT);

			int x = int((1 - radius) * temp1 + radius * temp2);
			int y = int((1 - radius) * temp3 + radius * temp4);

			image_out[r * NORM_WIDTH + theta] =
					image_in[y * MAX_WIDTH_CASIA + x];
		}
	}
}

void norm_low(uint8_t image_in[MAX_HEIGHT_CASIA * MAX_WIDTH_CASIA],
		uint8_t image_out[NORM_HEIGHT * NORM_WIDTH], ap_uint<9> values[6]) {
	ap_uint<9> x_p = values[0];
	ap_uint<9> y_p = values[1];
	ap_uint<9> r_p = values[2];
	ap_uint<9> r_i = values[3];

	for (int theta = 0; theta < NORM_WIDTH; theta++) {
		// max. ~340 -> 9 int places, 4 decimal places
		ap_ufixed<13,9> temp1, temp2, temp3, temp4;

		floatSin tempSin;
		floatSin tempCos;
		floatArg arg = theta * DEGtoRAD;
		cordic360_COS_SIN_fix(arg,tempSin,tempCos,5);


		temp1 = (ap_ufixed<13,9>) (x_p + r_p * tempCos);
		temp2 = (ap_ufixed<13,9>) (x_p + r_i * tempCos);
		temp3 = (ap_ufixed<13,9>) (y_p + r_p * tempSin);
		temp4 = (ap_ufixed<13,9>) (y_p + r_i * tempSin);

		//TODO maybe turn the loop so that only one bitshift operation for each loop cycle would turn the picture
		for (int r = 0; r < NORM_HEIGHT; r++) {
			ap_ufixed<8, 0> radius = ((ap_ufixed<16, 8> ) r) >> 5;

			ap_uint<9> x = (ap_uint<9> ) ((1 - radius) * temp1 + radius * temp2);
			ap_uint<9> y = (ap_uint<9> ) ((1 - radius) * temp3 + radius * temp4);
			//ap_uint<17> pos = y * MAX_WIDTH_CASIA + x;
			int pos = y.to_int() * MAX_WIDTH_CASIA + x.to_int();//array index require normal int!
			image_out[r * NORM_WIDTH + theta] = image_in[pos];
		}
	}
}
