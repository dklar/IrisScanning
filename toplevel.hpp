#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

#include "segmentation.hpp"
#include "gabor.hpp"
#include "normalization.hpp"

void top_level(AXI_STREAM& inputStream, AXI_STREAM& outputStream);

void arrayMethod(AXI_STREAM& INPUT_STREAM, uint8_t code[BITCODE_LENGTH]);
void arrayMethodschnell(AXI_STREAM& INPUT_STREAM, uint8_t code[BITCODE_LENGTH]);
void arrayMethod_fix(AXI_STREAM& INPUT_STREAM, uint8_t code[BITCODE_LENGTH]);
void test_detection_top(AXI_STREAM& inputStream, int& x, int& y, int& r1,
		int& r2);
void top_level_compare_gabor(AXI_STREAM& inputStream,
		uint8_t code[BITCODE_LENGTH], uint8_t codeFIX[BITCODE_LENGTH]);
