#include "toplevel.hpp"
#include <ap_fixed.h>
#include <hls_opencv.h>
#include "hls_math.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const std::string casia1path = "C://Users//Dennis//VivadoHLS//Final//Database//CASIA1//";
const std::string IITDpath   = "C://Users//Dennis//VivadoHLS//Final//Database//IITD Database//";
std::string databasePath =IITDpath;
int i =0;
void test_segmentaion(const char* path, int &r1,int &r2,int &x, int &y){
	IplImage* src_image = new IplImage;
	IplImage* dst_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;
	src_image = cvLoadImage(path);//load image file
	dst_image = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT), src_image->depth,src_image->nChannels);
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream

	uint8_t imageIn[MAX_HEIGHT*MAX_WIDTH];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img4(MAX_HEIGHT, MAX_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

#pragma HLS DATAFLOW
	uint8_t 				fifo1[MAX_WIDTH * MAX_HEIGHT];
	hlsCanny::Pixel 		fifo2[MAX_WIDTH * MAX_HEIGHT];
	uint8_t   				fifo3[MAX_WIDTH * MAX_HEIGHT];
	uint8_t   				fifo4[MAX_WIDTH * MAX_HEIGHT];
	uint8_t   				fifo5[MAX_WIDTH * MAX_HEIGHT];
	uint8_t   				fifo6[MAX_WIDTH * MAX_HEIGHT];
	uint8_t   				fifo7[NORM_WIDTH * NORM_HEIGHT];
	int						histogramm[6];

#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
#pragma HLS STREAM variable=fifo4 depth=1 dim=1


	hls::AXIvideo2Mat(src_stream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	hls::Duplicate(img1, img2, img3);
	hls::GaussianBlur<5,5>(img2, img4);

	hlsCanny::MatToArray<MAX_WIDTH,MAX_HEIGHT>(img4,fifo1);
	hlsCanny::SobelXY<MAX_WIDTH, MAX_HEIGHT>(fifo1, fifo2);
	hlsCanny::NonMaxSuppression<MAX_WIDTH, MAX_HEIGHT>(fifo2,fifo3);
	hlsCanny::HystThreshold<MAX_WIDTH, MAX_HEIGHT>(fifo3,fifo4,160,150);
	hlsCanny::getPossibleCircles<MAX_WIDTH, MAX_HEIGHT>(fifo4,20,250,x,y,r1);
	hls::Mat2Array<MAX_WIDTH>(img3, fifo5);
	//hlsCanny::createHistogramm<MAX_WIDTH,MAX_HEIGHT>(fifo5,histogramm);
	Iris(fifo5,fifo6, x, y,r1, r2);
	//norm_float(fifo6, fifo7, x,y,r1,r2);
	//hlsCanny::ArrayToMat<NORM_WIDTH,NORM_HEIGHT>(fifo7, img5);
	//hls::Mat2AXIvideo(img5, iris_in_stream);
	//AXIvideo2IplImage(iris_in_stream, dst_image);
	//cvSaveImage((std::to_string(i)+".jpg").c_str(), dst_image);
	//i++;
}
void test_segmentaion_stream(const char* path, int &r1,int &r2,int &x, int &y){
	IplImage* src_image = new IplImage;
	IplImage* dst_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;
	src_image = cvLoadImage(path);//load image file
	dst_image = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT), src_image->depth,src_image->nChannels);
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream

	uint8_t imageIn[MAX_HEIGHT*MAX_WIDTH];
	uint8_t imageOut[NORM_HEIGHT*NORM_WIDTH];
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img3(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img4(MAX_HEIGHT, MAX_WIDTH);
	NORM_RGB_IMAGE  img5(NORM_HEIGHT, NORM_WIDTH);

#pragma HLS DATAFLOW
	uint8_t 		fifo1[MAX_WIDTH * MAX_HEIGHT];
	uint8_t			fifo2[MAX_WIDTH * MAX_HEIGHT];


#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
#pragma HLS STREAM variable=fifo4 depth=1 dim=1


	hls::AXIvideo2Mat(src_stream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1, r1, x, y, 5, img2);
	hls::Mat2Array<MAX_WIDTH>(img2, fifo1);
	Iris(fifo1,fifo2,x,y,r1,r2);
}

void test_segmentation_top(int N){
	remove("eye.txt");
	fstream f;
	f.open("eye.txt", ios::app);

	for (int i=1;i<=N;i++){
		std::string path =
				i < 10 ? databasePath + "00" + std::to_string(i) + "//*" :
				i < 100 ?
						databasePath + "0" + std::to_string(i) + "//*" :
						databasePath + std::to_string(i) + "//*";
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = FindFirstFile(path.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
		    printf ("FindFirstFile failed (%d)\n", GetLastError());
		    return;
		}
		path = path.substr(0, path.size()-1);
		do{
			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				std::string pathTemp = path + FindFileData.cFileName;
				std::cout << pathTemp<<"\n";
				int r1,r2,x,y;
				test_segmentaion(pathTemp.c_str(),r1,r2,x,y);
				f << pathTemp<<"#" << x <<"#" << y<<"#" << r1 <<"#" <<r2<<"\n";
			}
		}while(FindNextFile(hFind, &FindFileData) != 0);

		FindClose(hFind);
	}
	f.close();
}

void test_vis(const char* path){
	IplImage* src_image = new IplImage;
	IplImage* dst_image = new IplImage;

	AXI_STREAM src_stream,dst_strm;
	src_image = cvLoadImage(path);//load image file
	dst_image = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT), src_image->depth,src_image->nChannels);
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream
	top_level_vis_float(src_stream,dst_strm);
	AXIvideo2IplImage(dst_strm, dst_image);
	cvSaveImage((std::to_string(i)+".jpg").c_str(), dst_image);
	i++;
}

void test_vis(std::string path, int x,int y,int r1, int r2){
	IplImage* src_image = new IplImage;
	IplImage* dst_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;
	src_image = cvLoadImage(path.c_str());//load image file
	dst_image = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT), src_image->depth,3);
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream

	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	NORM_RGB_IMAGE img2(NORM_HEIGHT, NORM_WIDTH);
	NORM_RGB_IMAGE img5(NORM_HEIGHT, NORM_WIDTH);
	NORM_GRAY_IMAGE hans;

#pragma HLS DATAFLOW
	uint8_t   			fifo3[MAX_WIDTH * MAX_HEIGHT];
	uint8_t   			fifo4[MAX_WIDTH * MAX_HEIGHT];

#pragma HLS STREAM variable=fifo1 depth=1 dim=1
#pragma HLS STREAM variable=fifo2 depth=1 dim=1
#pragma HLS STREAM variable=fifo3 depth=1 dim=1
#pragma HLS STREAM variable=fifo4 depth=1 dim=1


	hls::AXIvideo2Mat(src_stream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	hls::Mat2Array<MAX_WIDTH>(img1, fifo3);
	norm_float(fifo3, fifo4, x,y,r1,r2);
	visualize_float(fifo4,img2);
	//hls::Array2Mat<360>(fifo4, hans);
	hls::Mat2AXIvideo(img2, iris_in_stream);
	AXIvideo2IplImage(iris_in_stream, dst_image);
	cvSaveImage((std::to_string(i)+"_gabor.jpg").c_str(), dst_image);
	i++;
}

void test_vis_top2(int N){
	ifstream file("C://Users//Dennis//VivadoHLS//Final//Iris-recognition//Results//genau.txt");
	string line;
	while (getline(file,line) ){
		std::stringstream test(line.c_str());
		std::string segment;
		int i=0;
		int x,y,r1,r2;
		std::string filename;
		while(std::getline(test, segment, '#')){
			switch(i){
				case 0:
					filename = segment;
					break;
				case 1:
					x = stoi(segment);
					break;
				case 2:
					y = stoi(segment);
					break;
				case 3:
					r1 = stoi(segment);
					break;
				case 4:
					r2 = stoi(segment);
					test_vis(filename,x,y,r1,r2);
					break;
				}
			i++;
		}

	}
}
void test_vis_top(int N){

	for (int i=1;i<=N;i++){
		std::string path =
				i < 10 ? databasePath + "00" + std::to_string(i) + "//*" :
				i < 100 ?
						databasePath + "0" + std::to_string(i) + "//*" :
						databasePath + std::to_string(i) + "//*";

		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = FindFirstFile(path.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
		    printf ("FindFirstFile failed (%d)\n", GetLastError());
		    return;
		}
		path = path.substr(0, path.size()-1);
		do{
			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				std::string pathTemp = path + FindFileData.cFileName;
				std::cout << pathTemp<<"\n";
				test_vis(pathTemp.c_str());
			}
		}while(FindNextFile(hFind, &FindFileData) != 0);

		FindClose(hFind);
	}
}

void test_gabor(const char* filename,int i){
	uint8_t bit_code[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 3;
	}
	IplImage* src_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;

	src_image = cvLoadImage(filename);

	IplImage2AXIvideo(src_image, src_stream);

	top_level_float(src_stream,bit_code);
	std::string path = std::to_string(i)+"_high.txt";
	fstream f;

	f.open(path.c_str(), ios::app);
	for (int i=0;i<2048;i++){
		f << std::to_string(bit_code[i]);
	}

	f.close();
	cvReleaseImage(&src_image);
}

void test_gabor_top(){
	std::string path ="C://Users//Dennis//VivadoHLS//Final//Database//IITD Database//001//*";

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(path.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf ("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	path = path.substr(0, path.size()-1);
	int i=0;
	do{
		if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ){
			std::string pathTemp = path + FindFileData.cFileName;
			std::cout << pathTemp<<"\n";
			test_gabor(pathTemp.c_str(),i);
			i++;
		}
	}while(FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
}

void test_gabor_fix(const char* filename,int i){
	ap_uint<2> bit_code[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 3;
	}
	IplImage* src_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;

	src_image = cvLoadImage(filename);

	IplImage2AXIvideo(src_image, src_stream);

	top_level_fix(src_stream,bit_code);
	std::string path = std::to_string(i)+"_16_15_FIX.txt";
	fstream f;

	f.open(path.c_str(), ios::app);
	for (int i=0;i<2048;i++){
		f << std::to_string(bit_code[i]);
	}

	f.close();
	cvReleaseImage(&src_image);
}

void test_gabor_top_fix(){
	std::string path ="C://Users//Dennis//VivadoHLS//Final//Database//IITD Database//001//*";

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(path.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf ("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	path = path.substr(0, path.size()-1);
	int i=0;
	do{
		if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ){
			std::string pathTemp = path + FindFileData.cFileName;
			std::cout << pathTemp<<"\n";
			test_gabor_fix(pathTemp.c_str(),i);
			i++;
		}
	}while(FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
}

void testCORDIC_fix(){
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(10);
	floatSin s = 0;
	floatSin c = 0;
	std::cout <<"Alpha\tsin\tcordicSin\n";
	for (int i = 0 ;i<=360;i++){
		float s1 = sin((float)i*DEGtoRAD);
		float c1 = cos((float)i*DEGtoRAD);
		floatArg arg = i*DEGtoRAD;
		float debugS = s.to_float();
		float debugC = c.to_float();
		float debugA = arg.to_float();
		cordic360_COS_SIN_fix(arg,s,c,5);
		std::cout <<  i << "\t" << s1 << "\t" << s <<"\n";

	}
}

void testCORDIC(){
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(9);
	float s = 0;
	float c = 0;
	std::cout <<"Alpha\tsin\tcordicSin\n";
	for (int i = 0 ;i<=360;i++){
		float s1 = sin(i*DEGtoRAD);
		float c1 = cos(i*DEGtoRAD);
		float arg = i*DEGtoRAD;
		cordic360_COS_SIN(arg,s,c,5);
		std::cout <<  i << "\t" << s1 << "\t" << s <<"\n";

	}
}

void testGaborKernel(){
	float gaborR[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float gaborI[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gaborI[i][j] = 0;
			gaborR[i][j] = 0;
		}
	}
	generateGaborKernel(5,gaborI,gaborR);
	std::cout << "\n\nimag=";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			std::cout << gaborI[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\nreal=";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			std::cout << gaborR[i][j]<<"\t";
		}
		std::cout << "\n";
	}

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gaborI[i][j] = 0;
			gaborR[i][j] = 0;
		}
	}
	generateGaborKernel(10,gaborI,gaborR);
	std::cout << "\n\nimag=";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			std::cout << gaborI[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\nreal=";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			std::cout << gaborR[i][j]<<"\t";
		}
		std::cout << "\n";
	}
}

void testGaborKernel_FIX(){
	floatGabor gabor[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatGabor gaborI[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gabor[i][j] = 0;
		}
	}
	generateGaborKernel_fix(5,gabor,gaborI);

	for (int i=0;i<5;i++){
		for (int j=0;j<5;j++){
			std::cout << gabor[i][j].to_float()<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gabor[i][j] = 0;
		}
	}
	generateGaborKernel_fix(10,gabor,gaborI);

	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			std::cout << gabor[i][j].to_float()<<"\t";
		}
		std::cout << "\n";
	}
}

void testSinKernel_FIX(){
	floatSin sin[MAX_KERN_SIZE];
	floatSin cos[MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
			sin[i] = 0;
	}
	generateSinKernel_fix(5,sin,cos);

	for (int i=0;i<5;i++){
		std::cout << sin[i].to_float()<<"\t";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
			sin[i] = 0;
	}
	generateSinKernel_fix(10,sin,cos);

	for (int i=0;i<10;i++){
		std::cout << sin[i].to_float()<<"\t";
	}
}

void testSinKernel(){
	float sin[MAX_KERN_SIZE];
	float cos[MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		sin[i] = 0;
		cos[i] = 0;
	}
	generateSinKernel(5,sin,cos);
	std::cout << "\n\n sin= ";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		std::cout << sin[i]<<"\t";
	}
	std::cout << "\n\n cos= ";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		std::cout << cos[i]<<"\t";
	}
	for (int i=0;i<MAX_KERN_SIZE;i++){
		sin[i] = 0;
		cos[i] = 0;
	}
	generateSinKernel(10,sin,cos);
	std::cout << "\n\n sin= ";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		std::cout << sin[i]<<"\t";
	}
	std::cout << "\n\n cos= ";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		std::cout << cos[i]<<"\t";
	}

}

void testGaussKernel(){
	float gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gauss[i][j] = 0;
		}
	}
	generateGaussKernel(5,8,gauss);

	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			std::cout << gauss[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gauss[i][j] = 0;
		}
	}
	generateGaussKernel(10,8,gauss);

	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			std::cout << gauss[i][j]<<"\t";
		}
		std::cout << "\n";
	}
}

void testGaussFixKernel(){
	floatGauss gauss[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gauss[i][j] = 0;
		}
	}
	generateGaussKernel_fix(5,8,gauss);

	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			std::cout << gauss[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gauss[i][j] = 0;
		}
	}
	generateGaussKernel_fix(10,8,gauss);

	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			std::cout << gauss[i][j]<<"\t";
		}
		std::cout << "\n";
	}
}

void testGabor(){
	std::cout<<"\n\n------------GABOR FLOAT-----------\n";
	testGaborKernel();
	std::cout<<"\n\n---------------FIXPOINT-----------\n";
	testGaborKernel_FIX();
	std::cout<<"\n\n";
}

void testSINKernel(){
	std::cout<<"\n\n------------SIN FLOAT-----------\n";
	testSinKernel();
	std::cout<<"\n\n---------------FIXPOINT-----------\n";
	testSinKernel_FIX();
	std::cout<<"\n\n";
}

void testGAUSS(){
	std::cout<<"\n\n------------GAUSS FLOAT-----------\n";
	testGaussKernel();
	std::cout<<"\n\n---------------FIXPOINT-----------\n";
	testGaussFixKernel();
	std::cout<<"\n\n";
}


int main(int argc, char *argv[]){
	//test_gabor_top();
	//std::cout<<"\n\n---------------FIXPOINT-----------\n";
	test_segmentation_top(5);
	//test_segmentation_top(5);
	//test_vis_top2(10);

	std::cout<<"ende\n";
	return 0;
}
