#include "toplevel.hpp"

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
using namespace std;

const std::string casia1path = "C://Users//Dennis//VivadoHLS//Final//Database//CASIA1//";
const std::string IITDpath   = "C://Users//Dennis//VivadoHLS//Final//Database//IITD Database//";
std::string databasePath =IITDpath;

void test_segmentaion(const char* path, int &r1,int &r2,int &x, int &y){
	IplImage* src_image = new IplImage;
	AXI_STREAM src_stream,iris_in_stream;
	src_image = cvLoadImage(path);//load image file
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream

	uint8_t imageIn[MAX_HEIGHT*MAX_WIDTH];
	RGB_IMAGE  img0(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img1(MAX_HEIGHT, MAX_WIDTH);
	GRAY_IMAGE img2(MAX_HEIGHT, MAX_WIDTH);
	hls::AXIvideo2Mat(src_stream, img0);
	hls::CvtColor<HLS_RGB2GRAY>(img0, img1);
	findPupil(img1,r1,x,y,5,img2);
	hls::Mat2Array<MAX_WIDTH>(img2, imageIn);
	Iris(imageIn, r1, x, y, r2);
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

	//arrayMethod_fix(src_stream,bit_code);
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

void create_gabor_codes(const char* path,const char* filename,uint8_t bit_code[BITCODE_LENGTH]){
	//Fill with data if full (1024) values are 4 -> invalid
	bit_code[BITCODE_LENGTH];
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

	cvReleaseImage(&src_image);
}

void test_main2(){
	std::string path;
	uint8_t bit_code[BITCODE_LENGTH];
	std::ofstream file("gaborcodes_4bit_5iter.dat",std::ofstream::binary| std::ofstream::app);

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
				create_gabor_codes(pathTemp.c_str(),FindFileData.cFileName,bit_code);
				file.write((char*)bit_code,BITCODE_LENGTH);
			}

		}while(FindNextFile(hFind, &FindFileData) != 0);

		FindClose(hFind);
	}
	file.close();

}

void testCORDIC_fix(){
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(10);
	floatSin s = 0;
	floatSin c = 0;
	std::cout <<"Alpha\tsin\tcordicSin\n";
	for (int i = 0 ;i<=360;i++){
		float s1 = sin(i*DEGtoRAD);
		float c1 = cos(i*DEGtoRAD);
		floatArg arg = i*DEGtoRAD;
		float debugS = s.to_float();
		float debugC = c.to_float();
		float debugA = arg.to_float();
		cordic360_COS_SIN_fix(arg,s,c,5);
		std::cout <<  i << "\t" << s1 << "\t" << s <<"\n";

	}
}

void simulate_gabor_codes(const char* path){
	//Fill with data if full (1024) values are 4 -> invalid
	uint8_t bit_code[BITCODE_LENGTH];
	uint8_t bit_code1[BITCODE_LENGTH];
	for (int i=0;i<2048;i++){
		bit_code[i] = 4;
		bit_code1[i] = 4;
	}

	IplImage* src_image = new IplImage;
	AXI_STREAM src_stream,iris_in_stream;
	src_image = cvLoadImage(path);//load image file
	IplImage2AXIvideo(src_image, src_stream);//convert image to AXI stream


	top_level_compare_gabor(src_stream,bit_code,bit_code1);

	int hd = 0;
	for (int i = 0;i<2048;i++){
		if(bit_code[i]!=4){
			if(bit_code[i] != bit_code1[i]){
				hd++;
			}
		}
	}
	float hamming = hd / 2048.0f;
	std::cout << hamming <<"\n";


	cvReleaseImage(&src_image);
}

void compareGabor(){
	std::string path;
	uint8_t bit_code[BITCODE_LENGTH];

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
				std::string pathTemp = path + FindFileData.cFileName;
				simulate_gabor_codes(pathTemp.c_str());
			}

		}while(FindNextFile(hFind, &FindFileData) != 0);

		FindClose(hFind);
	}
}

void test_main3(){
	std::string path;
	remove("eye.txt");
	for (int i = 1; i< 100;i++){//ordner
		if (i<10){
			path = "C://Users//Dennis//OneDrive//Dokumente//Informatik//Iris recognition//Iris_detection_dennis//CASIA1//"+std::to_string(i)+"//00"+std::to_string(i)+"_1_1.jpg";
		}else{
			path = "C://Users//Dennis//OneDrive//Dokumente//Informatik//Iris recognition//Iris_detection_dennis//CASIA1//"+std::to_string(i)+"//0"+std::to_string(i)+"_1_1.jpg";
		}
		simulate_gabor_codes(path.c_str());
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
	float gabor[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float gaborI[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gabor[i][j] = 0;
		}
	}
	generateGaborKernel(3,gabor,gaborI);

	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			std::cout << gabor[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			gabor[i][j] = 0;
		}
	}
	generateGaborKernel(10,gabor,gaborI);

	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			std::cout << gabor[i][j]<<"\t";
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
	generateGaborKernel_fix(4,gabor,gaborI);

	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			std::cout << gabor[i][j]<<"\t";
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
			std::cout << gabor[i][j]<<"\t";
		}
		std::cout << "\n";
	}
}

void testSinKernel_FIX(){
	floatSin sin[MAX_KERN_SIZE][MAX_KERN_SIZE];
	floatSin cos[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			sin[i][j] = 0;
		}
	}
	generateSinKernel_fix(4,sin,cos);

	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			std::cout << sin[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			sin[i][j] = 0;
		}
	}
	generateSinKernel_fix(10,sin,cos);

	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			std::cout << sin[i][j]<<"\t";
		}
		std::cout << "\n";
	}
}

void testSinKernel(){
	float sin[MAX_KERN_SIZE][MAX_KERN_SIZE];
	float cos[MAX_KERN_SIZE][MAX_KERN_SIZE];
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	std::cout.precision(6);

	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			sin[i][j] = 0;
		}
	}
	generateSinKernel(4,sin,cos);

	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			std::cout << sin[i][j]<<"\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	for (int i=0;i<MAX_KERN_SIZE;i++){
		for (int j=0;j<MAX_KERN_SIZE;j++){
			sin[i][j] = 0;
		}
	}
	generateSinKernel(10,sin,cos);

	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){
			std::cout << sin[i][j]<<"\t";
		}
		std::cout << "\n";
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
	test_segmentation_top(100);

	return 0;
}
