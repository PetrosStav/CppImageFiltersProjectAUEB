#include "BlurFilter.h"

namespace imaging {

	BlurFilter::BlurFilter(Image * source):RegionFilter(source){}

	BlurFilter::~BlurFilter(){}

	void BlurFilter::apply_filter(){

		Image copy(*img);																						//make a copy of the original Image
		Color pixel_arr[3][3];																					//initialize the 3x3 region
		Color* source_buffer = img->getRawDataPtr();															//get the data pointer from the source Image
		Color* img_buffer = copy.getRawDataPtr();																//get the data pointer from the copy Image
		unsigned width = img->getWidth();																		//get the width
		unsigned height = img->getHeight();																		//get the height
		//for each pixel in the Image
		for (unsigned i = 0; i < height; i++) {
			for (unsigned j = 0; j < width; j++) {
				unsigned V = find_region(i, j, pixel_arr, source_buffer, width, height);						//find the valid region, populate the data to pixel_arr and return the valid pixels
				Color sum = Color(component_t(0), component_t(0), component_t(0));								//initialize sum of Colors
				//for every pixel in the region
				for (unsigned n = 0; n < 3; n++) {
					for (unsigned m = 0; m < 3; m++) {
						sum += pixel_arr[n][m];																	//make a sum of the Color values
					}
				}
				sum /= V;																						//find the mean of the Colors using the valid pixels
				//for every pixel in the region
				for (unsigned n = 0; n < 3; n++) {
					for (unsigned m = 0; m < 3; m++) {
						if (pixel_arr[n][m] == Color(component_t(0), component_t(0), component_t(0))) continue;	//if it has default value don't apply it
						img_buffer[(i - 1 + n)*width + (j - 1 + m)] = sum;										//change the pixel in the Image with the mean value
					}
				}
			}
		}
		*img = copy;																							//apply the changes to the source Image
	}


}
