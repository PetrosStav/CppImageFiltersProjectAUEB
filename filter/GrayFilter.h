#ifndef _GRAY_FILTER_
#define _GRAY_FILTER_

#include "Filter.h"

namespace imaging {
	class GrayFilter : public Filter{	

	public:

		/*! Constructor with reference to the image passed as an argument
		 *	
		 *	\param source is the source of the image to copy to an internal image
		 */
		GrayFilter(Image* source);

		/*! The GrayFilter destructor
		 *
		 * Declared virtual because Filter destructor is virtual.
		 */
		virtual ~GrayFilter();

		/*! Implement the gray filter to our copy of the image
		*
		* Each pixel of the image is initially p(i,j) = R(i,j),G(i,j),B(i,j)\n
		* After applying the filter, it becomes p'(i,j) = (𝜇,𝜇,𝜇),\n
		* where 𝜇 = [R(i,j) + G(i,j) + B(i,j)] / 3
		*/
		virtual void apply_filter();

	};
}

#endif