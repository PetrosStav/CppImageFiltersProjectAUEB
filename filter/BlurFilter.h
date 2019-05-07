#ifndef _BLUR_FILTER_
#define _BLUR_FILTER_

#include "RegionFilter.h"

namespace imaging {
	class BlurFilter : public RegionFilter {

	public:

		/*! Constructor with reference to the image passed as an argument
		*
		* \param source is the source of the image to copy to an internal image
		*/
		BlurFilter(Image* source);

		/*! The BlurFilter destructor
		*
		* Declared virtual because Filter destructor is virtual.
		*/
		virtual ~BlurFilter();

		/*! Implement the Blur filter to our copy of the image
		*
		* For each pixel(i,j) of the final image, read a 3x3 area of the input image
		* and set as color of the pixel(i,j) the average of the 9 colours of the 3x3 block
		*/
		virtual void apply_filter();

	};
}

#endif