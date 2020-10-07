#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

//template<int RESULT_W, int RESULT_H, int INTERN_W, int INTERN_H>
void encode_fix(uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		uint8_t bit_code[BITCODE_LENGTH]);

template<int RESULT_W, int RESULT_H, int INTERN_W, int INTERN_H>
ap_uint<2> gaborPixel_fix(int rho, int phi,
		uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH], int filter_size,
		ap_fixed<RESULT_W, RESULT_H> sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		ap_fixed<RESULT_W, RESULT_H> cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

template<int RESULT_W, int RESULT_H, int INTERN_W, int INTERN_H>
void generateGaborKernel_fix(int kern_size,
		ap_fixed<RESULT_W, RESULT_H> sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		ap_fixed<RESULT_W, RESULT_H> cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

template<int RESULT_W,int RESULT_H,int INTERN_W,int INTERN_H>
void generateGaussKernel_fix(int kern_size,
		ap_fixed<RESULT_W,RESULT_H> gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]);




void encode(uint8_t norm_img[NORM_HEIGHT*NORM_WIDTH],uint8_t bit_code[BITCODE_LENGTH]);

uint8_t gaborPixel(int rho, int phi, uint8_t norm_img[NORM_HEIGHT * NORM_WIDTH],
		int filter_size, float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateGaborKernel(int kern_size,
		float sin_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE],
		float cos_filter_matrix[MAX_KERN_SIZE][MAX_KERN_SIZE]);

void generateGaussKernel(int kern_size,
		float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE]);
