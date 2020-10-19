#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

void norm_float(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH],
		uint8_t image_out[NORM_HEIGHT * NORM_WIDTH], int &x, int &y, int &r1,
		int &r2);
void norm_fix(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH],
		uint8_t image_out[NORM_HEIGHT * NORM_WIDTH], ap_uint<9> &x,
		ap_uint<9> &y, ap_uint<9> &r1, ap_uint<9> &r2);
