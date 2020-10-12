#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

void findPupil(GRAY_IMAGE& img, int& r, int& x, int& y, GRAY_IMAGE &dst_img);

void findPupil2(GRAY_IMAGE& img, int& r, int& x, int& y, GRAY_IMAGE &dst_img);

void find_iris_high_accuracy(GRAY_IMAGE& img, int& pupilRadius, int& x, int& y,
		int& irisRadius, GRAY_IMAGE &dst_img);

void find_iris_low_accuracy(GRAY_IMAGE& img, int& pupilRadius, int& x, int& y,
		int& irisRadius, GRAY_IMAGE &dst_img);

void Iris(uint8_t image_in[MAX_HEIGHT_CASIA * MAX_WIDTH_CASIA],
		int& pupilRadius, int& x, int& y, int &irisRadius);
