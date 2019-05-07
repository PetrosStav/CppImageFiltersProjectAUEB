#include "GrayFilter.h"

namespace imaging {

	
	GrayFilter::GrayFilter(Image * source):Filter(source){}

	GrayFilter::~GrayFilter(){}

	void GrayFilter::apply_filter(){

		Color* buffer = img->getRawDataPtr();	//create a pointer to the internal data of the image
		unsigned width = img->getWidth();		//get the width of the image
		unsigned height = img->getHeight();		//get the height of the image
		unsigned size = width*height;			//calculate the size of the image
		for (unsigned i = 0; i < size; i++) {	//for each pixel in the image
			component_t mean = (buffer[i].r + buffer[i].g + buffer[i].b) / 3;	//caclulate the mean value of the 3 RGB components
			//store the mean RGB value to all 3 RGB components, creating the gray shade
			buffer[i].r = mean;					
			buffer[i].g = mean;
			buffer[i].b = mean;
		}

	}
}