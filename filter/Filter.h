#ifndef _FILTER_
#define _FILTER_

#include "Image.h"

namespace imaging {
	class Filter {
	
	protected:

		Image* img;	/*!< a temporary internal copy of the image*/

	public:

		/*! Constructor with reference to the image passed as an argument
		*
		* \param source is the source of the image to copy to an internal image
		*/
		Filter(Image* source) {
			img = source;
		}

		/*! The Filter destructor
		 *
		 * Declared virtual so that the destructors of derived classes will be called if we delete their objects
		 */
		virtual ~Filter() {}

		/*! Apply a filter to our image
		*
		* To edit an image and change its colour and appearance, we apply to each pixel an operator\n
		* which transforms its colour attribute to a new one. This can be local, by producing a new colour based on the old one,\n
		* or it can depend on other pixels, usually close to it.
		*/
		virtual void apply_filter() = 0;

	};
}

#endif