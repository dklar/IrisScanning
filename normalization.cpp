#include "normalization.hpp"

void norm_float(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH],
		uint8_t image_out[NORM_HEIGHT * NORM_WIDTH], int &x, int &y, int &r1,
		int &r2) {

	for (int theta = 0; theta < NORM_WIDTH; theta++) {
		float thetaDot = theta * DEGtoRAD;
		float temp1, temp2, temp3, temp4;
		float tempSin, tempCos;

		tempSin = sin(thetaDot);
		tempCos = cos(thetaDot);
		temp1 = (float) (x + r1 * tempCos);
		temp2 = (float) (x + r2 * tempCos);
		temp3 = (float) (y + r1 * tempSin);
		temp4 = (float) (y + r2 * tempSin);

		for (int r = 0; r < NORM_HEIGHT; r++) {
			float radius = r / ((float) NORM_HEIGHT);

			int x_tmp = int((1 - radius) * temp1 + radius * temp2);
			int y_tmp = int((1 - radius) * temp3 + radius * temp4);

			image_out[r * NORM_WIDTH + theta] = image_in[y_tmp * MAX_WIDTH
					+ x_tmp];
		}
	}
}

void norm_fix(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH],
		uint8_t image_out[NORM_HEIGHT * NORM_WIDTH], ap_uint<9> &x, ap_uint<9> &y, ap_uint<9> &r1,
		ap_uint<9> &r2) {

	for (int theta = 0; theta < NORM_WIDTH; theta++) {
		// max. ~340 -> 9 int places, 4 decimal places
		ap_ufixed<13,9> temp1, temp2, temp3, temp4;

		floatSin tempSin;
		floatSin tempCos;
		floatArg arg = theta * DEGtoRAD;
		cordic360_COS_SIN_fix(arg,tempSin,tempCos,5);


		temp1 = (ap_ufixed<13,9>) (x + r1 * tempCos);
		temp2 = (ap_ufixed<13,9>) (x + r2 * tempCos);
		temp3 = (ap_ufixed<13,9>) (y + r1 * tempSin);
		temp4 = (ap_ufixed<13,9>) (y + r2 * tempSin);

		//TODO maybe turn the loop so that only one bitshift operation for each loop cycle would turn the picture
		for (int r = 0; r < NORM_HEIGHT; r++) {
			ap_ufixed<8, 0> radius = ((ap_ufixed<16, 8> ) r) >> 5;

			ap_uint<9> x = (ap_uint<9> ) ((1 - radius) * temp1 + radius * temp2);
			ap_uint<9> y = (ap_uint<9> ) ((1 - radius) * temp3 + radius * temp4);

			int pos = y.to_int() * MAX_WIDTH + x.to_int();//array index require normal int!
			image_out[r * NORM_WIDTH + theta] = image_in[pos];
		}
	}
}
