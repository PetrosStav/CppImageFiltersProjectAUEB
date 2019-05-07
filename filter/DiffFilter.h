#ifndef _DIFF_FILTER_
#define _DIFF_FILTER_

#include "RegionFilter.h"

namespace imaging {
	class DiffFilter : public RegionFilter {

	public:

		/*! Constructor with reference to the image passed as an argument
		*
		* \param source is the source of the image to copy to an internal image
		*/
		DiffFilter(Image* source);

		/*! The DiffFilter destructor
		*
		* Declared virtual because Filter destructor is virtual.
		*/
		virtual ~DiffFilter();

		/*! Implement the Diff filter to our copy of the image
		 *
		 * Read the RGB values of the colours in a 3x3 area and sort them, individually for each component
		 * Calculate the final color component as the difference between the min and max value
		 */
		virtual void apply_filter();

	};
}

#endif