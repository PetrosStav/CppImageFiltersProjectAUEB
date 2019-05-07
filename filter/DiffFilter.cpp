#include <algorithm>
#include "DiffFilter.h"

namespace imaging {

	DiffFilter::DiffFilter(Image * source) :RegionFilter(source) {}

	DiffFilter::~DiffFilter() {}

	void DiffFilter::apply_filter() {

		Image copy(*img);										//make a copy of the original Image
		Color pixel_arr[3][3];									//initialize the 3x3 region
		Color* source_buffer = img->getRawDataPtr();			//get the data pointer from the source Image
		Color* img_buffer = copy.getRawDataPtr();				//get the data pointer from the copy Image
		unsigned width = img->getWidth();						//get the width
		unsigned height = img->getHeight();						//get the height
		//for each pixel in the Image
		for (unsigned i = 0; i < height; i++) {
			for (unsigned j = 0; j < width; j++) {
				unsigned V = find_region(i, j, pixel_arr, source_buffer, width, height);	//find the valid region, populate the data to pixel_arr and return the valid pixels
				component_t* r_channel = new component_t[V];								//initialize an array for the red channel
				component_t* g_channel = new component_t[V];								//initialize an array for the green channel
				component_t* b_channel = new component_t[V];								//initialize an array for the blue channel
				unsigned v = 0;																//initialize counter
				for (unsigned n = 0; n < 3; n++) {
					for (unsigned m = 0; m < 3; m++) {
						if (pixel_arr[n][m] == Color(component_t(0), component_t(0), component_t(0))) continue;	//if default value continue loop
						unsigned idx = v++;																		//increase counter
						r_channel[idx] = pixel_arr[n][m].r;														//put red value of Color to red channel
						g_channel[idx] = pixel_arr[n][m].g;														//put red value of Color to green channel
						b_channel[idx] = pixel_arr[n][m].b;														//put red value of Color to blue channel
					}
				}
				//sort each channel
				std::sort(r_channel, r_channel + V);
				std::sort(g_channel, g_channel + V);
				std::sort(b_channel, b_channel + V);

				Color diff = Color(r_channel[(V - 1)] - r_channel[0], g_channel[(V - 1)] - g_channel[0], b_channel[(V - 1)] - b_channel[0]);	//find the difference between the max and min value and make a Color with this difference

				//free memory
				delete[] r_channel;
				delete[] g_channel;
				delete[] b_channel;

				//for every pixel in the region
				for (unsigned n = 0; n < 3; n++) {
					for (unsigned m = 0; m < 3; m++) {
						if (pixel_arr[n][m] == Color(component_t(0), component_t(0), component_t(0))) continue;	//if default value continue loop
						img_buffer[(i - 1 + n)*width + (j - 1 + m)] = diff;										//change the pixel in the Image with the diff Color
					}
				}
			}
		}
		*img = copy;																							//apply the changes to the source Image
	}
}