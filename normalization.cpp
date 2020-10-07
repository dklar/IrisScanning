#include "normalization.hpp"

void norm_high(unsigned char image_in[MAX_HEIGHT_CASIA * MAX_WIDTH_CASIA],
		unsigned char image_out[NORM_HEIGHT * NORM_WIDTH], int values[6]) {
	int x_p = values[0];
	int y_p = values[1];
	int r_p = values[2];
	int r_i = values[3];

	int rows = MAX_HEIGHT_CASIA;
	int cols = MAX_WIDTH_CASIA;

	for (int theta = 0; theta < NORM_WIDTH; theta++) {
		float thetaDot = theta * DEGtoRAD;
		float temp1, temp2, temp3, temp4;
		float tempSin, tempCos;

		tempSin = sin(thetaDot);
		tempCos = cos(thetaDot); //hls::
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

void norm_low(unsigned char image_in[MAX_HEIGHT_CASIA * MAX_WIDTH_CASIA],
		unsigned char image_out[NORM_HEIGHT * NORM_WIDTH], int values[6]) {
	int x_p = values[0];
	int y_p = values[1];
	int r_p = values[2];
	int r_i = values[3];

	int rows = MAX_HEIGHT_CASIA;
	int cols = MAX_WIDTH_CASIA;

	for (int theta = 0; theta < NORM_WIDTH; theta++) {
		//float thetaDot = theta*DEGtoRAD;
		float temp1, temp2, temp3, temp4;
		float tempSin, tempCos;

		tempCos = cordic360_Cos_fixed(theta * DEGtoRAD, 10).to_float();
		tempSin = cordic360_Sin_fixed(theta * DEGtoRAD, 10).to_float();

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
