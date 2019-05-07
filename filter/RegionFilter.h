#ifndef _REGION_FILTER_
#define _REGION_FILTER_

#include "Filter.h"

/*! \file RegionFilter.h */

namespace imaging {
	class RegionFilter : public Filter {
	
	public:

		/*! Constructor with reference to the image passed as an argument
		*
		* \param source is the source of the image to copy to an internal image
		*/
		RegionFilter(Image* source) :Filter(source) {}

		/*! The Filter destructor
		 *
		 * Declared virtual because Filter destructor is virtual.
		 */
		virtual ~RegionFilter(){}

		/*! Apply a filter to our image
		 *
		 * For each pixel(i,j) of the final image, the region filters use an area N(x)M pixels\n
		 * around the position(i,j) of the initial image to calculate the color. In this way, they can "see"\n
		 * what is happening in the area near a point of the image and not in an isolated pixel.
		 */
		virtual void apply_filter() = 0;
		
		/*! Find the valid pixels in the 3x3 region
		 *
		 * The 3x3 region is centered in each Pixel in the Image and the valid pixels that are not\n
		 * out of bounds are being filled with data from the Image. 
		 *
		 * \param i the row of the central pixel
		 * \param j the column of the central pixel
		 * \param arr[3][3] the 3x3 region
		 * \param source_buffer 
		 * \param width the image width
		 * \param height the image height
		 *
		 * \return the number of valid pixels in the region
		 */
		unsigned find_region(const unsigned& i, const unsigned& j, Color arr[3][3], Color* source_buffer, const unsigned& width, const unsigned& height) {
			unsigned V = 9;																		//we start with 9 valid pixels
			int r,c;																			//initialize variables for row and column
			for (unsigned n = 0; n < 3; n++) {													//for each row of arr[3][3]
				for (unsigned m = 0; m < 3; m++) {												//for each column of arr[3][3]
					r = i - 1 + n;																//calculate the index of row
					c = j - 1 + m;																//calculate the index of column
					if (r < 0 || r >= height || c < 0 || c >= width) {							//if the indexes are out of bounds in the image
						arr[n][m] = Color(component_t(0), component_t(0), component_t(0));		//we use a black Color to fill the pixel in that position of arr[3][3]
						V--;																	//we will count one pixel less
						continue;																//continue the loop
					}
					arr[n][m] = source_buffer[r*width + c];										//we get the pixel data from the pixel and set it to the arr[3][3]
				}
			}
			return V;																			//return all the valid pixels in the region
		}
		
	};
}

#endif