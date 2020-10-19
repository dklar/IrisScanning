#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

#include "segmentation.hpp"
#include "gabor.hpp"
#include "normalization.hpp"

void top_level_float(AXI_STREAM& inputStream,uint8_t code[BITCODE_LENGTH]);
void top_level_fix(AXI_STREAM& inputStream,ap_uint<2> code[BITCODE_LENGTH]);


void top_level_vis_float(AXI_STREAM& inputStream,AXI_STREAM& outputStream);
void top_level_vis_fix(AXI_STREAM& inputStream,AXI_STREAM& outputStream);
