#include "segmentation.hpp"


/**
 * threshold for casia ~70
 * threshold for IITD ~0
 */
void findPupil(GRAY_IMAGE &img, int &r, int &x, int &y, int threshold, GRAY_IMAGE &dst_img)
{
	PIXELGRAY pixel_value;
	int startX_line = 0;
	int length_line = 0;
	int gap_count = 0;	   //how many pixel are between
	const int max_gap = 10; //10;//if more pixel are between this and a further black pixel the line is ending
	int longest_line_in_row = 0;
	int start_longest_lineX = 0;

	bool is_line = false;

	int total_longest_line = 0;
	int total_y = 0;
	int total_x = 0;

loopPixel:
	for (int y = 0; y < MAX_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_WIDTH; x++)
		{
#pragma HLS loop_flatten off
#pragma HLS pipeline II = 1
			img >> pixel_value;
			dst_img << pixel_value;
			if (pixel_value.val[0] <= threshold)
			{
				//pixel is black
				if (!is_line)
				{
					startX_line = x;
					length_line = 1;
					is_line = true;
				}
				else
				{
					length_line += 1;
				}
				gap_count = 0;
			}
			else
			{
				//pixel is not black,the white noise in pupil
				if (is_line)
				{
					gap_count += 1;
					length_line += 1;
					if (gap_count >= max_gap)
					{
						//noise are to big, line is ending
						length_line -= max_gap;
						is_line = false;
						gap_count = 0;
						if (length_line > longest_line_in_row)
						{
							longest_line_in_row = length_line;
							length_line = 0;
							start_longest_lineX = startX_line;
							if (longest_line_in_row > total_longest_line)
							{
								total_longest_line = longest_line_in_row;
								total_x = startX_line;
								total_y = y;
							}
						}
					}
				}
			}
		}
	}

	r = (int)total_longest_line / 2;
	x = total_x + r;
	y = total_y;
}

void find_iris_high_accuracy(GRAY_IMAGE &img, int &pupilRadius, int &x, int &y, int &irisRadius, GRAY_IMAGE &dst_img)
{
	int i_max = 0;
	int iris_radius = 0;

	//int points[IRIS_RADIUS_MAX - IRIS_RADIUS_MIN + 2][6][3];//iris raius max - min 6 punkte 0,45,... x/y
	int points[(IRIS_RADIUS_MAX - IRIS_RADIUS_MIN + 2) * 6 * 2]; //37 radien jeweils mit 6 punkten mit x und y
	int count1 = 0;
	int count2 = 0;
	//calc points we have compute
	for (int r = IRIS_RADIUS_MIN - 1; r < IRIS_RADIUS_MAX + 1; r++)
	{
		count2 = 0;
		for (int alpha = 0; alpha < 360; alpha += 45)
		{
			float sinus = replaceSIN(alpha);
			float cosinus = replaceCOS(alpha);
			int cx = x + r * cosinus;
			int cy = y + r * sinus;
			points[count1 * 12 + count2 * 2 + 0] = cx;
			points[count1 * 12 + count2 * 2 + 1] = cy;
			count2++;
		}
		count1++;
	}

	PIXELGRAY pixel_value;
	int sums[37]; //37*6*2/12=737 summen aller kreise
	for (int i = 0; i < 37; i++)
		sums[i] = 0;
	int count = 0;
loopPixel:
	for (int y = 0; y < MAX_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_WIDTH; x++)
		{
			//#pragma HLS loop_flatten off
			//#pragma HLS pipeline II=1
			img >> pixel_value;
			dst_img << pixel_value;
			for (int p = 0; p < 444; p += 2)
			{
				if (points[p] == x and points[p + 1] == y)
				{
					int pos = (int)p / 12;
					sums[pos] += pixel_value.val[0];
				}
			}
		}
	}
	int sum1 = 0;
	int sum2 = 0;
	for (int r = 1; r < 37; r++)
	{
		sum1 = sums[r + 1];
		sum2 = sums[r - 1];
		int diff = sum1 - sum2;
		if (diff > i_max)
		{
			i_max = diff;
			iris_radius = r; //bester kreis ist nummer r von der ersten schleife
		}
	}

	irisRadius = IRIS_RADIUS_MIN + iris_radius;
}

void find_iris_low_accuracy(GRAY_IMAGE &img, int &pupilRadius, int &x, int &y, int &irisRadius, GRAY_IMAGE &dst_img)
{
	int i_max = 0;
	int iris_radius = 0;

	//int points[IRIS_RADIUS_MAX - IRIS_RADIUS_MIN + 2][6][3];//iris raius max - min 6 punkte 0,45,... x/y
	int points[37 * 6 * 2]; //37 radien jeweils mit 6 punkten mit x und y
	int count1 = 0;
	int count2 = 0;
	//calc points we have compute
	for (int r = IRIS_RADIUS_MIN - 1; r < IRIS_RADIUS_MAX + 1; r++)
	{
		count2 = 0;
		for (int alpha = 0; alpha < 360; alpha += 45)
		{
			if (alpha != 90 and alpha != 270)
			{
				int cx = x + r * replaceCOS(alpha);
				int cy = y + r * replaceSIN(alpha);
				points[count1 * 12 + count2 * 2 + 0] = cx;
				points[count1 * 12 + count2 * 2 + 1] = cy;
				count2++;
			}
		}
		count1++;
	}

	PIXELGRAY pixel_value;
	int sums[37]; //37*6*2/12=737 summen aller kreise
	for (int i = 0; i < 37; i++)
		sums[i] = 0;
	int count = 0;
loopPixel:
	for (int y = 0; y < MAX_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_WIDTH; x++)
		{
			//#pragma HLS loop_flatten off
			//#pragma HLS pipeline II=1
			img >> pixel_value;
			dst_img << pixel_value;
			for (int p = 0; p < 444; p += 2)
			{
				if (points[p] == x and points[p + 1] == y)
				{
					int pos = (int)p / 12;
					sums[pos] += pixel_value.val[0];
				}
			}
		}
	}
	int sum1 = 0;
	int sum2 = 0;
	for (int r = 1; r < 37; r++)
	{
		sum1 = sums[r + 1];
		sum2 = sums[r - 1];
		int diff = sum1 - sum2;
		if (diff > i_max)
		{
			i_max = diff;
			iris_radius = r; //bester kreis ist nummer r von der ersten schleife
		}
	}

	irisRadius = IRIS_RADIUS_MIN + iris_radius;
}

/*
 * Weiss ->groﬂ 255
 */
void Iris(uint8_t image_in[MAX_HEIGHT * MAX_WIDTH],
		uint8_t image_out[MAX_HEIGHT * MAX_WIDTH], int &x, int &y,
		int &pupilRadius, int &irisRadius) { //uint8_t *histogramm,

	//create a histogram, by actually not creating a histogram, divide color space(0..255) into 5 groups
	//hist_inner is the histogram value of the inner Hull integral of the iris
	//IrisSegmentaionLoop is checking if we reached a other histogram step, to make sure, that is not just coincidence, that
	//the outer Hull integral is bigger(brighter) than the inner Hull integral it have to be 3 times successively

	int hist_inner = calcCircleSum3(image_in, x, y, IRIS_RADIUS_MIN) / 50;
	int count=0;
	IrisSegmentaionLoop:
	//for (int r = pupilRadius + 30; r < pupilRadius * 4;r++) {
	for(int r = IRIS_RADIUS_MIN;r<IRIS_RADIUS_MAX;r++){
#pragma HLS unroll
		int hist_outer = calcCircleSum3(image_in, x, y, r) / 50;
		if (hist_outer > hist_inner){
			count++;
			irisRadius = r;//if we don't reach the condition below, we want to return the most coincidence value (so with section change)
			if(count>3){
				irisRadius = r-3;
				break;
			}
		}else{
			count=0;
		}
	}
	image_out = image_in;
}



