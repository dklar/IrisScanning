#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

//template<int RESULT_W, int RESULT_H, int INTERN_W, int INTERN_H>
void encode_fix(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],ap_uint<1> bit_code[BITCODE_LENGTH]);

void gaborPixel_fix(int rho, int phi,
		uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH], int filter_size,
		floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		ap_uint<1> code[BITCODE_LENGTH], int pos);

void generateGaborKernel_fix(int kern_size,
		floatGabor sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatGabor cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateGaussKernel_fix(int kern_size, int peak,
		floatGauss gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateSinKernel(int kern_size, float sin[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateSinKernel_fix(int kern_size,
		floatSin sin[MAX_KERN_SIZE][MAX_KERN_SIZE],
		floatSin cos[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void encode(uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		uint8_t bit_code[BITCODE_LENGTH]);

uint8_t gaborPixel(int rho, int phi, uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		int filter_size, float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateGaborKernel(int kern_size,
		float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateGaussKernel(int kern_size, int peak,
		float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]);
