#include "hls_video.h"
#include <ap_fixed.h>
#include "hls_math.h"
//#include <stdint.h>

//-----differnt image sizes of database--------
//-----to change database set MAX_WIDTH/ MAX_HEIGHT either to _CASIA or _IITD

#define MAX_TEST_WIDTH 432
#define MAX_TEST_HEIGHT 48


#define MAX_WIDTH_CASIA  320
#define MAX_HEIGHT_CASIA  280

#define MAX_WIDTH_IITD 320
#define MAX_HEIGHT_IITD 240
//----End------


#define MAX_WIDTH MAX_WIDTH_IITD
#define MAX_HEIGHT MAX_HEIGHT_IITD

#define IRIS_RADIUS_MIN 85
#define IRIS_RADIUS_MAX 150

#define PUPIL_RADIUS_MIN 30
#define PUPIL_RADIUS_MAX  60


#define NORM_HEIGHT 32//48//32
#define NORM_WIDTH  360//432//360

#define MAX_KERN_SIZE NORM_HEIGHT/3

#define ENCODED_PIXELS  1024     //should be divisible by 32(int) or 64(long)
#define BITCODE_LENGTH  2048     //each encoded pixel brings 2 bits to the bitcode

typedef hls::stream<ap_axiu<32,1,1,1> > 					AXI_STREAM;//32 bit data stream
typedef hls::Mat<MAX_HEIGHT,   MAX_WIDTH,  HLS_8UC3> 		RGB_IMAGE;//RGB image from type HLS::Mat
typedef hls::Mat<MAX_HEIGHT,   MAX_WIDTH,  HLS_8UC1> 		GRAY_IMAGE;//Gray image from type HLS::Mat
typedef hls::Mat<NORM_HEIGHT,NORM_WIDTH,   HLS_8UC3> 		NORM_RGB_IMAGE;//RGB image from type HLS::Mat
typedef hls::Mat<NORM_HEIGHT,NORM_WIDTH,   HLS_8UC1> 		NORM_GRAY_IMAGE;//Gray image from type HLS::Mat
typedef hls::Scalar<3, uint8_t> 							RGBPIXEL;
typedef hls::Scalar<1, uint8_t> 							PIXELGRAY;


typedef ap_uint<2> int2;//for return value of gabor pixel ->00,01,10,11
typedef ap_uint<6> int6;//for other small values
