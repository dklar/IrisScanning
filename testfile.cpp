#include "toplevel.hpp"

#include <hls_opencv.h>
#include "hls_math.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

using namespace std;

void test_picture(const char* filename,int i){
	IplImage* src_image = new IplImage;
	IplImage* dst_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;

	src_image = cvLoadImage(filename);
	dst_image = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT), src_image->depth, src_image->nChannels);


	IplImage2AXIvideo(src_image, src_stream);

	top_level(src_stream,iris_in_stream);
	AXIvideo2IplImage(iris_in_stream, dst_image);


	cvSaveImage((std::to_string(i)+"_cord_8_10.jpg").c_str(), dst_image);
	cvReleaseImage(&src_image);
	cvReleaseImage(&dst_image);
}

void test_detection(const char* filename,int i){
	IplImage* src_image = new IplImage;
	AXI_STREAM src_stream;
	int r1,r2,x,y;

	src_image = cvLoadImage(filename);
	IplImage2AXIvideo(src_image, src_stream);
	test_detection_top(src_stream,x,y,r1,r2);

	fstream f;
	f.open("eye.txt", ios::app);
	f << std::to_string(i)<<"#" << x <<"#" << y<<"#" << r1 <<"#" <<r2<<"\n";
	f.close();

	cvReleaseImage(&src_image);
}

void test_gabor(const char* filename,int i){
	uint8_t bit_code[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 4;
	}
	IplImage* src_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;

	src_image = cvLoadImage(filename);

	IplImage2AXIvideo(src_image, src_stream);

	arrayMethod(src_stream,bit_code);
	std::string path = "gabor_all_high_"+std::to_string(i)+".txt";
	fstream f;

	f.open(path.c_str(), ios::app);
	for (int i=0;i<2048;i++){
		f << std::to_string(bit_code[i]);
	}

	f.close();
	cvReleaseImage(&src_image);
}

void test_gabor_fix(const char* filename,int i){
	uint8_t bit_code[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 4;
	}
	IplImage* src_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;

	src_image = cvLoadImage(filename);

	IplImage2AXIvideo(src_image, src_stream);

	arrayMethod_fix(src_stream,bit_code);
	std::string path = "gabor_fix_5_iter_"+std::to_string(i)+".txt";
	fstream f;

	f.open(path.c_str(), ios::app);
	for (int i=0;i<2048;i++){
		f << std::to_string(bit_code[i]);
	}

	f.close();
	cvReleaseImage(&src_image);
}

void test_gabor2(const char* filename,int i){
	uint8_t bit_code[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 4;
	}
	IplImage* src_image = new IplImage;

	AXI_STREAM src_stream,iris_in_stream;

	src_image = cvLoadImage("C://Users//Dennis//Desktop//Iris//schnell.jpg");

	IplImage2AXIvideo(src_image, src_stream);

	arrayMethodschnell(src_stream,bit_code);
	std::string path = "gabor_all_high_"+std::to_string(i)+".txt";
	fstream f;

	f.open(path.c_str(), ios::app);
	for (int i=0;i<2048;i++){
		f << std::to_string(bit_code[i]);
	}

	f.close();
	cvReleaseImage(&src_image);
}

void test_main(){
	std::string path;
	remove("eye.txt");
	for (int i = 1; i< 100;i++){//ordner
		if (i<10){
			path = "C://Users//Dennis//OneDrive//Dokumente//Informatik//Iris recognition//Iris_detection_dennis//CASIA1//"+std::to_string(i)+"//00"+std::to_string(i)+"_1_1.jpg";
		}else{
			path = "C://Users//Dennis//OneDrive//Dokumente//Informatik//Iris recognition//Iris_detection_dennis//CASIA1//"+std::to_string(i)+"//0"+std::to_string(i)+"_1_1.jpg";
		}
		test_gabor_fix(path.c_str(),i);
	}
}

void create_gabor_codes(const char* path,const char* filename ){
	//Fill with random data
	uint8_t bit_code[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 4;
	}

	IplImage* src_image = new IplImage;
	AXI_STREAM src_stream,iris_in_stream;
	src_image = cvLoadImage(path);//load image file
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream

	std::string gabor_filename;
	std::string temp = filename;

	arrayMethod(src_stream,bit_code);
	//arrayMethod_fix(src_stream,bit_code);

	gabor_filename = "gabor_acc_"+temp;
	gabor_filename = gabor_filename.substr(0, gabor_filename.length()-3);//remove "jpg"
	gabor_filename +="txt";//and replace it with "txt"


	fstream f;
	f.open(gabor_filename.c_str(), ios::app);
	for (int i=0;i<2048;i++){
		f << std::to_string(bit_code[i]);
	}
	f.close();

	cvReleaseImage(&src_image);
}

void test_main2(){
	std::string path;
	remove("eye.txt");
	for (int i=1;i<=100;i++){
		path  = "C://Users//Dennis//VivadoHLS//Final//Database//CASIA1//"+std::to_string(i)+"//*";
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = FindFirstFile(path.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
		    printf ("FindFirstFile failed (%d)\n", GetLastError());
		    return;
		}
		path = path.substr(0, path.size()-1);
		do {

			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				//file
				std::string pathTemp = path + FindFileData.cFileName;
				std::cout << pathTemp<<"\n";
				create_gabor_codes(pathTemp.c_str(),FindFileData.cFileName);
			}

		}while(FindNextFile(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}



}

void testCORDIC(){
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);
	float s=0;
	float c=0;
	std::cout <<"Alpha\tsin\tcordicSin\tcos\tcordicCos\n";
	for (int i = 0 ;i<=360;i++){
		float s1 = sin(i*DEGtoRAD);
		float c1 = cos(i*DEGtoRAD);
		cordic360_COS_SIN(i*DEGtoRAD,s,c,20);
		float rel = ((s1-s)/s1)*100;
		float absErr = abs(((s1-s)/s1)*100);
		std::cout.precision(3);
		std::cout <<  i << "\t" << s1 << "\t" << s <<"\t"<< c1 <<"\t"<< c<<"\n";

	}
}

void testCORDIC_fix(){
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);
	float s=0;
	float c=0;
	std::cout <<"Alpha\tsin\tcordicSin\tcos\tcordicCos\n";
	for (int i = 0 ;i<=360;i++){
		float s1 = sin(i*DEGtoRAD);
		float c1 = cos(i*DEGtoRAD);
		cordic360_COS_SIN_fix(i*DEGtoRAD,s,c,20);
		float rel = ((s1-s)/s1)*100;
		float absErr = abs(((s1-s)/s1)*100);
		std::cout.precision(3);
		std::cout <<  i << "\t" << s1 << "\t" << s <<"\t"<< rel <<"\t"<< absErr<<"\n";

	}
}

void test(){
	ap_fixed<8,0> a = 0.00390625;
	ap_fixed<8,0> b = 0.5;
	ap_fixed<8,0> c = a+b;
	std::cout << c.to_float();




}

int main(int argc, char *argv[]){
	test_main2();
}
