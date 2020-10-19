#include "toplevel.hpp"


void iris_scanning_float(AXI_STREAM& inputStream,uint8_t code[BITCODE_LENGTH]){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	int x,y,r1,r2;
#pragma HLS dataflow
	uint8_t fifo1[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo2[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo3[NORM_HEIGHT * NORM_WIDTH];
#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1, r1, x, y, 5, img2);
	hls::Mat2Array<MAX_WIDTH>(img2, fifo1);
	Iris_fix_border(fifo1, r1, x, y, r2,fifo2);
	norm_float(fifo2, fifo3, x,y,r1,r2);
	encode(fifo3,code);
	//std::cout << x <<";"<<y<<";"<<r1<<";"<<r2<<"\n";

}

void iris_scanning_fix(AXI_STREAM& inputStream,ap_uint<2> code[BITCODE_LENGTH]){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	int x,y,r1,r2;
#pragma HLS dataflow
	uint8_t fifo1[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo2[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo3[NORM_HEIGHT * NORM_WIDTH];
#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1, r1, x, y, 5, img2);
	hls::Mat2Array<MAX_WIDTH>(img2, fifo1);
	Iris_fix_border(fifo1, r1, x, y, r2,fifo2);
	norm_float(fifo2, fifo3, x,y,r1,r2);
	encode_fix(fifo3,code);
}

void iris_visualize_float(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	int x,y,r1,r2;
#pragma HLS dataflow
	uint8_t fifo1[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo2[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo3[NORM_HEIGHT * NORM_WIDTH];
#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1, r1, x, y, 5, img2);
	hls::Mat2Array<MAX_WIDTH>(img2, fifo1);
	Iris_fix_border(fifo1, r1, x, y, r2,fifo2);
	norm_float(fifo2, fifo3, x,y,r1,r2);
	visualize_float(fifo3,img5);
	hls::Mat2AXIvideo(img5, outputStream);

}

void iris_visualize_fix(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	int x,y,r1,r2;
#pragma HLS dataflow
	uint8_t fifo1[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo2[MAX_HEIGHT * MAX_WIDTH];
	uint8_t fifo3[NORM_HEIGHT * NORM_WIDTH];
#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1, r1, x, y, 5, img2);
	hls::Mat2Array<MAX_WIDTH>(img2, fifo1);
	Iris_fix_border(fifo1, r1, x, y, r2,fifo2);
	norm_float(fifo2, fifo3, x,y,r1,r2);
	visualize_fix(fifo3,img5);
	hls::Mat2AXIvideo(img5, outputStream);
}

void top_level_vis_float(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=code
#pragma HLS INTERFACE ap_ctrl_none port=return
	iris_visualize_float(inputStream,outputStream);
}
void top_level_vis_fix(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=code
#pragma HLS INTERFACE ap_ctrl_none port=return
	top_level_vis_fix(inputStream,outputStream);
}

void top_level_float(AXI_STREAM& inputStream,uint8_t code[BITCODE_LENGTH]){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=code
#pragma HLS INTERFACE ap_ctrl_none port=return
	iris_scanning_float(inputStream,code);
}

void top_level_fix(AXI_STREAM& inputStream,ap_uint<2> code[BITCODE_LENGTH]){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=code
#pragma HLS INTERFACE ap_ctrl_none port=return
	iris_scanning_fix(inputStream,code);
}
