#ifndef HEADER
#define HEADER
#include "definitions.hpp"
#include "sine.hpp"
#endif

void findPupil(GRAY_IMAGE &img, int &r, int &x, int &y, int threshold, GRAY_IMAGE &dst_img);

void findPupil2(GRAY_IMAGE &img, int &r, int &x, int &y, int threshold, GRAY_IMAGE &dst_img);

void find_iris_high_accuracy(GRAY_IMAGE &img, int &pupilRadius, int &x, int &y,
							 int &irisRadius, GRAY_IMAGE &dst_img);

void find_iris_low_accuracy(GRAY_IMAGE &img, int &pupilRadius, int &x, int &y,
							int &irisRadius, GRAY_IMAGE &dst_img);

void Iris(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH], int &pupilRadius, int &x,
		int &y, int &irisRadius, uint8_t image_out[MAX_HEIGHT * MAX_WIDTH]);

void Iris_fix_border(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH], int &pupilRadius, int &x,
		int &y, int &irisRadius, uint8_t image_out[MAX_HEIGHT * MAX_WIDTH]);
namespace hlsCanny{

	enum Direction{
		GRAD_0,
		GRAD_45,
		GRAD_90,
		GRAD_135
	};

	struct Pixel{
		uint8_t color;
		Direction dir;
	};

	struct line{
		int begin;
		int end;
	};

	class Canny{
	public:
		template<int w,int h>
		static void ArrayToMat(uint8_t* in,hls::Mat<h,w,HLS_8UC3> &out);

		template<int w,int h>
		static void MatToArray(GRAY_IMAGE &in, uint8_t* out);

        template<uint32_t WIDTH, uint32_t HEIGHT>
        static void SobelXY(uint8_t* src, Pixel* dst);

        template<uint32_t WIDTH, uint32_t HEIGHT>
        static void NonMaxSuppression(Pixel* src, uint8_t* dst);

        template<uint32_t WIDTH, uint32_t HEIGHT>
        static void HystThreshold(uint8_t* src, uint8_t* dst, uint8_t hthr, uint8_t low_threshold);

        template<uint32_t WIDTH, uint32_t HEIGHT>
        static void HystThresholdComp(uint8_t* src, uint8_t* dst);

        template<int w,int h>
        static void show0degree(Pixel* src, uint8_t* dst);

    	template<int w,int h>
    	void getPossibleCircles(uint8_t* src,int minimum,int threshold,int &x,int &y,int &r);
	};

	template<int w,int h>
	void MatToArray(GRAY_IMAGE &in, uint8_t* out){
		PIXELGRAY pixel_value;

		loopPixel:
		for (int y=0;y<h;y++){
			for (int x=0;x<w;x++){
				#pragma HLS loop_flatten off
				#pragma HLS pipeline II=1
				in >> pixel_value;
				out[x+y*w] = pixel_value.val[0];
			}
		}
	}

	template<int w,int h>
	void ArrayToMat(uint8_t* in, hls::Mat<h,w,HLS_8UC3> &out){
		RGBPIXEL px1;

		backConvertLoop:
		for (int y=0;y<h;y++){
			for(int x=0;x<w;x++){
				#pragma HLS PIPELINE II=1
                #pragma HLS LOOP_FLATTEN off
				px1.val[0] = in[x+y*w];
				px1.val[1] = in[x+y*w];
				px1.val[2] = in[x+y*w];
				out << px1;
			}
		}
	}

	template<uint32_t WIDTH, uint32_t HEIGHT>
	void SobelXY(uint8_t* src, Pixel* dst) {
	        const int KERNEL_SIZE = 3;

	        uint8_t line_buf[KERNEL_SIZE][WIDTH];
	        uint8_t window_buf[KERNEL_SIZE][KERNEL_SIZE];

	        #pragma HLS ARRAY_RESHAPE variable=line_buf complete dim=1
	        #pragma HLS ARRAY_PARTITION variable=window_buf complete dim=0

	        //-- 3x3 Horizontal Sobel kernel
	        const int H_SOBEL_KERNEL[KERNEL_SIZE][KERNEL_SIZE] = {  { 1,  0, -1},
	                                                                { 2,  0, -2},
	                                                                { 1,  0, -1}   };
	        //-- 3x3 vertical Sobel kernel
	        const int V_SOBEL_KERNEL[KERNEL_SIZE][KERNEL_SIZE] = {  { 1,  2,  1},
	                                                                { 0,  0,  0},
	                                                                {-1, -2, -1}   };

	        #pragma HLS ARRAY_PARTITION variable=H_SOBEL_KERNEL complete dim=0
	        #pragma HLS ARRAY_PARTITION variable=V_SOBEL_KERNEL complete dim=0

	        // image proc loop
	        for(int yi = 0; yi < HEIGHT; yi++) {
	            for(int xi = 0; xi < WIDTH; xi++) {
	                #pragma HLS PIPELINE II=1
	                #pragma HLS LOOP_FLATTEN off

	                //--- sobel
	                int pix_sobel;
	                Direction grad_sobel;

	                //-- line buffer
	                for(int yl = 0; yl < KERNEL_SIZE - 1; yl++) {
	                    line_buf[yl][xi] = line_buf[yl + 1][xi];
	                }
	                // write to line buffer
	                line_buf[KERNEL_SIZE - 1][xi] = src[xi + yi*WIDTH];

	                //-- window buffer
	                for(int yw = 0; yw < KERNEL_SIZE; yw++) {
	                    for(int xw = 0; xw < KERNEL_SIZE - 1; xw++) {
	                        window_buf[yw][xw] = window_buf[yw][xw + 1];
	                    }
	                }
	                // write to window buffer
	                for(int yw = 0; yw < KERNEL_SIZE; yw++) {
	                    window_buf[yw][KERNEL_SIZE - 1] = line_buf[yw][xi];
	                }

	                //-- convolution
	                int pix_h_sobel = 0;
	                int pix_v_sobel = 0;

	                // convolution using by holizonal kernel
	                for(int yw = 0; yw < KERNEL_SIZE; yw++) {
	                    for(int xw = 0; xw < KERNEL_SIZE; xw++) {
	                        pix_h_sobel += window_buf[yw][xw] * H_SOBEL_KERNEL[yw][xw];
	                    }
	                }

	                // convolution using by vertical kernel
	                for(int yw = 0; yw < KERNEL_SIZE; yw++) {
	                    for(int xw = 0; xw < KERNEL_SIZE; xw++) {
	                        pix_v_sobel += window_buf[yw][xw] * V_SOBEL_KERNEL[yw][xw];
	                    }
	                }

	                //pix_sobel = hls::sqrt(float(pix_h_sobel * pix_h_sobel + pix_v_sobel * pix_v_sobel));
	                pix_sobel = hls::abs(pix_h_sobel)  + hls::abs(pix_v_sobel);

	                // to consider saturation
	                if(255 < pix_sobel) {
	                    pix_sobel = 255;
	                }

	                // evaluate gradient direction
	                int t_int;
	                if(pix_h_sobel != 0) {
	                    t_int = pix_v_sobel * 256 / pix_h_sobel;
	                }
	                else {
	                    t_int = 0x7FFFFFFF;
	                }

	                // 112.5° ~ 157.5° (tan 112.5° ~= -2.4142, tan 157.5° ~= -0.4142)
	                if(-618 < t_int && t_int <= -106) {
	                    grad_sobel = GRAD_135;
	                }
	                // -22.5° ~ 22.5° (tan -22.5° ~= -0.4142, tan 22.5° = 0.4142)
	                else if(-106 < t_int && t_int <= 106) {
	                    grad_sobel = GRAD_0;
	                }
	                // 22.5° ~ 67.5° (tan 22.5° ~= 0.4142, tan 67.5° = 2.4142)
	                else if(106 < t_int && t_int < 618) {
	                    grad_sobel = GRAD_45;
	                }
	                // 67.5° ~ 112.5° (to inf)
	                else {
	                    grad_sobel = GRAD_90;
	                }

	                // output
	                if((KERNEL_SIZE < xi && xi < WIDTH - KERNEL_SIZE) &&
	                   (KERNEL_SIZE < yi && yi < HEIGHT - KERNEL_SIZE)) {
	                    dst[xi + yi*WIDTH].color = pix_sobel;
	                    dst[xi + yi*WIDTH].dir  = grad_sobel;
	                }
	                else {
	                    dst[xi + yi*WIDTH].color = 0;
	                    dst[xi + yi*WIDTH].dir  = grad_sobel;
	                }
	            }
	        }
	    }

	template<uint32_t WIDTH, uint32_t HEIGHT>
	void NonMaxSuppression(Pixel* src, uint8_t* dst) {
		const int WINDOW_SIZE = 3;

		Pixel line_buf[WINDOW_SIZE][WIDTH];
		Pixel window_buf[WINDOW_SIZE][WINDOW_SIZE];

		#pragma HLS ARRAY_RESHAPE variable=line_buf complete dim=1
		#pragma HLS ARRAY_PARTITION variable=window_buf complete dim=0

		NonMaxLoop:
		for(int yi = 0; yi < HEIGHT; yi++) {
			for(int xi = 0; xi < WIDTH; xi++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS LOOP_FLATTEN off


				uint8_t value_nms;
				Direction grad_nms;

				//-- line buffer
				for(int yl = 0; yl < WINDOW_SIZE - 1; yl++) {
					line_buf[yl][xi] = line_buf[yl + 1][xi];
				}
				// write to line buffer
				line_buf[WINDOW_SIZE - 1][xi] = src[xi + yi*WIDTH];

				//-- window buffer
				for(int yw = 0; yw < WINDOW_SIZE; yw++) {
					for(int xw = 0; xw < WINDOW_SIZE - 1; xw++) {
						window_buf[yw][xw] = window_buf[yw][xw + 1];
					}
				}
				// write to window buffer
				for(int yw = 0; yw < WINDOW_SIZE; yw++) {
					window_buf[yw][WINDOW_SIZE - 1] = line_buf[yw][xi];
				}

				value_nms = window_buf[WINDOW_SIZE / 2][WINDOW_SIZE / 2].color;
				grad_nms = window_buf[WINDOW_SIZE / 2][WINDOW_SIZE / 2].dir;

				/**
				 * 00000
				 * 0xxx0
				 * 00000
				 */
				if(grad_nms == GRAD_0) {
					if(value_nms < window_buf[WINDOW_SIZE / 2][0].color ||
					   value_nms < window_buf[WINDOW_SIZE / 2][WINDOW_SIZE - 1].color) {
						value_nms = 0;
					}
				}

				/**
				 * 0x000
				 * 00x00
				 * 000x0
				 * upper left, bottom right
				 */
				else if(grad_nms == GRAD_45) {
					if(value_nms < window_buf[0][0].color ||
					   value_nms < window_buf[WINDOW_SIZE - 1][WINDOW_SIZE - 1].color) {
						value_nms = 0;
					}
				}
				/**
				 * 00x00
				 * 00x00
				 * 00x00
				 * upper , bottom
				 */
				else if(grad_nms == GRAD_90) {
					if(value_nms < window_buf[0][WINDOW_SIZE - 1].color ||
					   value_nms < window_buf[WINDOW_SIZE - 1][WINDOW_SIZE / 2].color) {
						value_nms = 0;
					}
				}
				// grad 135° -> bottom left, upper right
				else if(grad_nms == GRAD_135) {
					if(value_nms < window_buf[WINDOW_SIZE - 1][0].color ||
					   value_nms < window_buf[0][WINDOW_SIZE - 1].color) {
						value_nms = 0;
					}
				}

				// output
				if((WINDOW_SIZE < xi && xi < WIDTH - WINDOW_SIZE) &&
				   (WINDOW_SIZE < yi && yi < HEIGHT - WINDOW_SIZE)) {
					dst[xi + yi*WIDTH] = value_nms;
				}
				else {
					dst[xi + yi*WIDTH] = 0;
				}
			}
		}
	}

	template<uint32_t WIDTH, uint32_t HEIGHT>
	void HystThreshold(uint8_t* src, uint8_t* dst, uint8_t hthr, uint8_t low_threshold) {

		ThresholdLoop:
		for(int yi = 0; yi < HEIGHT; yi++) {
			for(int xi = 0; xi < WIDTH; xi++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS LOOP_FLATTEN off

				//--- hysteresis threshold
				int pix_hyst;

				if(src[xi + yi*WIDTH] < low_threshold) {
					pix_hyst = 0;
				}
				else if(src[xi + yi*WIDTH] > hthr) {
					pix_hyst = 255;
				}
				else {
					pix_hyst = 1;
				}

				// output
				dst[xi + yi*WIDTH] = pix_hyst;
			}
		}
	}

	template<uint32_t WIDTH, uint32_t HEIGHT>
	void HystThresholdComp(uint8_t* src, uint8_t* dst) {
		const int WINDOW_SIZE = 3;

		uint8_t line_buf[WINDOW_SIZE][WIDTH];
		uint8_t window_buf[WINDOW_SIZE][WINDOW_SIZE];

		#pragma HLS ARRAY_RESHAPE variable=line_buf complete dim=1
		#pragma HLS ARRAY_PARTITION variable=window_buf complete dim=0

		// image proc loop
		for(int yi = 0; yi < HEIGHT; yi++) {
			for(int xi = 0; xi < WIDTH; xi++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS LOOP_FLATTEN off

				//--- non-maximum suppression
				uint8_t pix_hyst = 0;

				//-- line buffer
				for(int yl = 0; yl < WINDOW_SIZE - 1; yl++) {
					line_buf[yl][xi] = line_buf[yl + 1][xi];
				}
				// write to line buffer
				line_buf[WINDOW_SIZE - 1][xi] = src[xi + yi*WIDTH];

				//-- window buffer
				for(int yw = 0; yw < WINDOW_SIZE; yw++) {
					for(int xw = 0; xw < WINDOW_SIZE - 1; xw++) {
						window_buf[yw][xw] = window_buf[yw][xw + 1];
					}
				}
				// write to window buffer
				for(int yw = 0; yw < WINDOW_SIZE; yw++) {
					window_buf[yw][WINDOW_SIZE - 1] = line_buf[yw][xi];
				}

				//-- comparison operation
				for(int yw = 0; yw < WINDOW_SIZE; yw++) {
					for(int xw = 0; xw < WINDOW_SIZE; xw++) {
						if(window_buf[WINDOW_SIZE / 2][WINDOW_SIZE / 2] != 0) {
							if(window_buf[yw][xw] == 0xFF) {
								pix_hyst = 0xFF;
							}
						}
					}
				}

				// output
				dst[xi + yi*WIDTH] = pix_hyst;
			}
		}
	}

	template<int w,int h>
	void getPossibleCircles(uint8_t* src,int minimum,int threshold,int &x,int &y,int &r){
		line line1;
		bool firstX = true;
		bool firstY = true;
		int votingX[w];
		int votingY[h];

#pragma HLS ARRAY_MAP variable=votingX instance=array3 horizontal
#pragma HLS ARRAY_MAP variable=votingY instance=array3 horizontal
		//horizontal -> array3[w+h]
		//vertical ->int32 array1;int32 array2 -> int64 array3

//TODO merge init Loops
		initVotingX:
		for (int i = 0;i<w;i++){
#pragma HLS pipeline II=1//no effect
			votingX[i] = 0;
		}
		initVotingY:
		for (int i = 0;i<h;i++){
#pragma HLS pipeline II=1
			votingY[i] = 0;
		}

		int radii[76];
		initRadiiLoop:
		for(int i=0;i<76;i++){
			radii[i]=0;
		}

		searchForX:
		for (int y = 0;y<h;y++){
			for(int x = 0;x<w;x++){
				if (src[x + y*w]>threshold){
					if (firstX){
						line1.begin = x;
						firstX = false;
					}
					if (!firstX){
						line1.end = x;
						int l = line1.end-line1.begin;
						if (l>minimum)
							votingX[line1.begin+l/2]+=1;
						line1.begin = x;
					}
				}
			}
		}
		line1.begin = 0;
		line1.end = 0;
		searchForY:
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				if (src[x + y*w]>threshold){
					if (firstY) {
						line1.begin = y;
						firstY = false;
					}
					if (!firstY) {
						line1.end = y;
						int l = line1.end - line1.begin;
						if (l > minimum)
							votingY[line1.begin + l / 2] += 1;
						line1.begin = y;
					}
				}
			}
		}
		int Xmax = 0;
		int Ymax = 0;
		int posX = 0;
		int posY = 0;

		for (int i = 0;i<w;i++){
			if (votingX[i]>Xmax){
				Xmax = votingX[i];
				posX = i;
			}
		}
		for (int i = 0;i<h;i++){
			if (votingY[i]>Ymax){
				Ymax = votingY[i];
				posY = i;
			}
		}

		bruteforceSearch:
		for (int x0 = 0; x0 < w; x0++) {
			int a = (x0-posX)*(x0-posX);
			for (int y0 = 0; y0 < h; y0++) {
				if (src[x0 + y0*w]>threshold){
					int b = (y0-posY)*(y0-posY);
					uint32_t c = a + b;
					if(c<=10000 || c>=625){
						 // possible range of radii
						 // rmin = 25  -> temp>=25^2=625
						 // rmax = 100 -> tmep<=100^2=10.000
						int radius = (int)hls::sqrt(c);
						radii[radius-25]+=1;
					}
				}
			}
		}

		int max=0;
		int r_temp=0;

		CheckLoop:
		for(int i=0;i<76;i++){
			if (radii[i]>max){
				max = radii[i];
				r_temp = i+25;
			}
		}
		x = posX;
		y = posY;
		r = r_temp;
	}

}
