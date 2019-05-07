#ifndef _COLOR_FILTER_
#define _COLOR_FILTER_

#include "Filter.h"

namespace imaging {
	class ColorFilter : public Filter {

	private:

		Color c;/*!< the RGB combination by which a pixel will be multiplied*/

	public:

		/*! Constructor with reference to the image passed as an argument
		 *
		 * \param source is the source of the image to copy to an internal image
		 * \param col is
		 */
		ColorFilter(Image* source,const Color& col);

		/*! The ColorFilter destructor
		 *
		 * Declared virtual because Filter destructor is virtual.
		 */
		virtual ~ColorFilter();

		/*! Implement the color filter to our copy of the image
		 *
		 *  A color consists of 3 parameters, c = (Rc,Gc,Bc)\n
		 *  which will be applied to the according color\n
		 * of each pixel, like this:\n
		 * p'(i,j) = c*p(i,j) = (Rc*R(i,j),Gc*G(i,j),Bc*B(i,j)
		 */
		virtual void apply_filter();

	};
}

#endif