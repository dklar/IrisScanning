#include "hls_video.h"
#include <ap_fixed.h>


#define MAX_WIDTH_CASIA  320
#define MAX_HEIGHT_CASIA  280

#define IRIS_RADIUS_MIN 85
#define IRIS_RADIUS_MAX 150

#define PUPIL_RADIUS_MIN 30
#define PUPIL_RADIUS_MAX  60


#define NORM_HEIGHT 64
#define NORM_WIDTH  360

#define MAX_KERN_SIZE NORM_HEIGHT/3

#define ENCODED_PIXELS  1024     //should be divisible by 32(int) or 64(long)
#define BITCODE_LENGTH  2048     //each encoded pixel brings 2 bits to the bitcode

typedef hls::stream<ap_axiu<32,1,1,1> > 								AXI_STREAM;//32 bit data stream
typedef hls::Mat<MAX_HEIGHT_CASIA,   MAX_WIDTH_CASIA,   HLS_8UC3> 		RGB_IMAGE;//RGB image from type HLS::Mat
typedef hls::Mat<MAX_HEIGHT_CASIA,   MAX_WIDTH_CASIA,   HLS_8UC1> 		GRAY_IMAGE;//Gray image from type HLS::Mat
typedef hls::Mat<64,   360,   HLS_8UC3> 								NORM_RGB_IMAGE;//RGB image from type HLS::Mat
typedef hls::Mat<64,   360,   HLS_8UC1> 								NORM_GRAY_IMAGE;//Gray image from type HLS::Mat
typedef hls::Scalar<3, uint8_t> 										PIXEL;
typedef hls::Scalar<1, uint8_t> 										PIXELGRAY;
typedef hls::Mat<64,   360,   HLS_8UC1>									GRAY_IMAGE_NORM;
typedef hls::Mat<64,   360,   HLS_8UC3>									RGB_IMAGE_NORM;

