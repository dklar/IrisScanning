#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

void norm_low(unsigned char image_in[MAX_HEIGHT_CASIA * MAX_WIDTH_CASIA],
		unsigned char image_out[NORM_HEIGHT * NORM_WIDTH], ap_uint<9> values[6]);

void norm_high(unsigned char image_in[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA],
		uint8_t image_out[NORM_HEIGHT*NORM_WIDTH],int values[6]);
