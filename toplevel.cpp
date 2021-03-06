#include "toplevel.hpp"

void writeValues(int values[6],int x, int y,int r1, int r2){
	values[0] = x;
	values[1] = y;
	values[2] = r1;
	values[3] = r2;
}
void writeValues(ap_uint<9> values[6],int x, int y,int r1, int r2){
	values[0] = x;
	values[1] = y;
	values[2] = r1;
	values[3] = r2;
}

void tmp(uint8_t imageIn[MAX_HEIGHT * MAX_WIDTH],
		uint8_t imageOut[NORM_HEIGHT * NORM_WIDTH], int& r1, int& x,
		int& y, int &r2) {
	ap_uint<9> val[6]={0,0,0,0,0,0};
	Iris(imageIn, r1, x, y, r2);
	writeValues(val, x, y, r1, r2);
	norm_low(imageIn, imageOut, val);
}

void arrayMethod_fix(AXI_STREAM& INPUT_STREAM,ap_uint<1> code[BITCODE_LENGTH]){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);
	int r1,r2,x,y;
	ap_uint<9> val[6]={0,0,0,0,0,0};

	uint8_t imageIn[MAX_HEIGHT*MAX_WIDTH];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);//iitd ~0 casia~70
	hls::Mat2Array<MAX_WIDTH>(img2, imageIn);
	tmp(imageIn,imageOut,r1,x,y,r2);
	encode_fix(imageOut,code);
}

void arrayMethod(AXI_STREAM& INPUT_STREAM, uint8_t code[BITCODE_LENGTH]) {
	RGB_IMAGE img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE img5(NORM_HEIGHT, NORM_WIDTH);
	int r1, r2, x, y;
	ap_uint<9> val[6] = { 0, 0, 0, 0, 0, 0 };

	uint8_t imageIn[MAX_HEIGHT * MAX_WIDTH];
	uint8_t imageOut[NORM_HEIGHT * NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1, r1, x, y,5, img2);
	find_iris_high_accuracy(img2, r1, x, y, r2, img3);
	hls::Mat2Array<MAX_WIDTH>(img3, imageIn);
	writeValues(val, x, y, r1, r2);
	norm_low(imageIn, imageOut, val);
	encode(imageOut, code);
}

void arrayMethodschnell(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]){
	NORM_RGB_IMAGE  img0(NORM_HEIGHT, NORM_WIDTH);
	NORM_GRAY_IMAGE img1(NORM_HEIGHT, NORM_WIDTH);

	int r1,r2,x,y;

	uint8_t imageIn[MAX_HEIGHT*MAX_WIDTH];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	hls::Mat2Array<NORM_WIDTH>(img1, imageOut);
	encode(imageOut,code);
	//code = bit_code;

}

void detectNormFix(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	unsigned char imageIn[MAX_WIDTH*MAX_HEIGHT];
	unsigned char imageOut[NORM_HEIGHT*NORM_WIDTH];

	int r1,r2,x,y;
	ap_uint<9> val[6]={0,0,0,0,0,0};
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	norm_low(imageIn,imageOut,val);
	hls::Array2Mat<NORM_WIDTH>(imageOut, img4);
	hls::CvtColor<HLS_GRAY2RGB>(img4, img5);
	hls::Mat2AXIvideo(img5, outputStream);
}

void detectNorm(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	unsigned char imageIn[MAX_WIDTH*MAX_HEIGHT];
	unsigned char imageOut[NORM_HEIGHT*NORM_WIDTH];

	int r1,r2,x,y;
	ap_uint<9> val[6]={0,0,0,0,0,0};
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	norm_low(imageIn,imageOut,val);
	hls::Array2Mat<NORM_WIDTH>(imageOut, img4);
	hls::CvtColor<HLS_GRAY2RGB>(img4, img5);
	hls::Mat2AXIvideo(img5, outputStream);
}

void detectNorm_float(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	unsigned char imageIn[MAX_WIDTH*MAX_HEIGHT];
	unsigned char imageOut[NORM_HEIGHT*NORM_WIDTH];

	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	norm_high(imageIn,imageOut,val);
	hls::Array2Mat<NORM_WIDTH>(imageOut, img4);
	hls::CvtColor<HLS_GRAY2RGB>(img4, img5);
	hls::Mat2AXIvideo(img5, outputStream);
}

void top_level_compare_gabor(AXI_STREAM& inputStream,uint8_t code[BITCODE_LENGTH],uint8_t codeFIX[BITCODE_LENGTH]){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=code
#pragma HLS INTERFACE s_axilite port=codeFIX
#pragma HLS INTERFACE ap_ctrl_none port=return

	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);
	int r1,r2,x,y;
	int val[6]={0,0,0,0,0,0};

	uint8_t imageIn[MAX_HEIGHT*MAX_WIDTH];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);
	hls::Mat2Array<MAX_WIDTH>(img3, imageIn);
	writeValues(val,x,y,r1,r2);
	norm_high(imageIn,imageOut,val);
	encode(imageOut,code);
	encode(imageOut,codeFIX);

}

void test_detection_top(AXI_STREAM& inputStream,int& x,int& y, int& r1, int& r2){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=y
#pragma HLS INTERFACE s_axilite port=r1
#pragma HLS INTERFACE s_axilite port=r2
#pragma HLS INTERFACE ap_ctrl_none port=return

	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);

#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	find_iris_high_accuracy(img2, r1, x, y,r2,img3);

}


void detect_Array(AXI_STREAM& inputStream,int& x,int& y, int& r1, int& r2){
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	NORM_GRAY_IMAGE img4(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

	uint8_t imageIn[MAX_WIDTH*MAX_HEIGHT];
#pragma HLS dataflow
	hls::AXIvideo2Mat(inputStream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	hls::Mat2Array<MAX_WIDTH>(img2, imageIn);
	Iris(imageIn,r1,x,y,r2);

}



void top_level(AXI_STREAM& inputStream,AXI_STREAM& outputStream){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE axis port=outputStream
#pragma HLS INTERFACE ap_ctrl_none port=return

}


void top_level2(AXI_STREAM& inputStream,ap_uint<1> code[BITCODE_LENGTH]){
#pragma HLS INTERFACE axis port=inputStream
#pragma HLS INTERFACE s_axilite port=code
#pragma HLS INTERFACE ap_ctrl_none port=return

	arrayMethod_fix(inputStream,code);
}
