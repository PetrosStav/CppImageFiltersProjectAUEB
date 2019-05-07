#include "ColorFilter.h"

namespace imaging {

	ColorFilter::ColorFilter(Image * source, const Color& col) :Filter(source),c(col) {}

	ColorFilter::~ColorFilter() {}

	void ColorFilter::apply_filter() {

		Color* buffer = img->getRawDataPtr();	//create a pointer to the internal data of the image
		unsigned width = img->getWidth();		//get the width of the image
		unsigned height = img->getHeight();		//get the height of the image
		unsigned size = width*height;			//calculate the size of the image
		for (unsigned i = 0; i < size; i++) {	//for each pixel in the image
			buffer[i].r *= c.r;					//store the red component to the buffer
			buffer[i].g *= c.g;					//store the green component to the buffer
			buffer[i].b *= c.b;					//store the blue component to the buffer
		}

	}
}