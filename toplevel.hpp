#include "definitions.hpp"
#include "sine.hpp"

void top_level(AXI_STREAM& inputStream,AXI_STREAM& outputStream);


void findPupil(GRAY_IMAGE& img, int& r, int& x, int& y,GRAY_IMAGE &dst_img);
void findPupil2(GRAY_IMAGE& img, int& r, int& x, int& y,GRAY_IMAGE &dst_img);
void find_iris_high_accuracy(GRAY_IMAGE& img, int& pupilRadius, int& x, int& y,int& irisRadius,GRAY_IMAGE &dst_img);
void find_iris_low_accuracy(GRAY_IMAGE& img, int& pupilRadius, int& x, int& y,int& irisRadius,GRAY_IMAGE &dst_img);

void core_high(unsigned char image_in[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA],unsigned char image_out[64*360],int values[6]);
void core_low(unsigned char image_in[MAX_HEIGHT_CASIA*MAX_WIDTH_CASIA],unsigned char image_out[64*360],int values[6]);

void arrayMethod(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]);
void arrayMethodschnell(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]);
void arrayMethod_fix(AXI_STREAM& INPUT_STREAM,uint8_t code[BITCODE_LENGTH]);
void test_detection_top(AXI_STREAM& inputStream,int& x,int& y, int& r1, int& r2);
