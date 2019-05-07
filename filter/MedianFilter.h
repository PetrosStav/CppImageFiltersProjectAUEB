#ifndef _MEDIAN_FILTER_
#define _MEDIAN_FILTER_

#include "RegionFilter.h"

namespace imaging {
	class MedianFilter : public RegionFilter {

	public:

		/*! Constructor with reference to the image passed as an argument
		*
		* \param source is the source of the image to copy to an internal image
		*/
		MedianFilter(Image* source);

		/*! The MedianFilter destructor
		*
		* Declared virtual because Filter destructor is virtual.
		*/
		virtual ~MedianFilter();

		/*! Implement the Median filter to our copy of the image
		 *
		 * Read the RGB values of the colours in a 3x3 area and sort them, individually for each component
		 * Calculate the final color component as the value of the middle element of the sorted components
		 */
		virtual void apply_filter();

	};
}

#endif