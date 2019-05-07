#ifndef _IMAGE_
#define _IMAGE_

#include "Array.h"
#include "Serializable.h"
#include "Vec3.h"

/*!\namespace imaging Contains every class or function associated with the image storage, compression and manipulation.
*/
namespace imaging {

	typedef float component_t;
	typedef math::Vec3<component_t> Color;

	class Image : public math::Array<Color>,public Serializable {

	public:

		// constructors and destructor

		/*! Default constructor.
		*
		* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		*/
		Image();

		/*! Constructor with width and height specification.
		*
		* \param w is the desired width of the new image.
		* \param h is the desired height of the new image.
		*/
		Image(unsigned int w, unsigned int h);

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		* \param data_ptr is the source of the data to copy to the internal image buffer.
		*
		* \see setData
		*/
		Image(unsigned int width, unsigned int height, const Color * data_ptr);

		/*! Copy constructor.
		*
		* \param src is the source image to replicate in this object.
		*/
		Image(const Image & source);

		/*! The Image destructor.
		*
		* Declared virtual because Array destructor is virtual.
		*/
		virtual ~Image();

		/*! Obtains a pointer to the internal data.
		*
		*  It cannot be deleted by the user, since it is const
		*/
		Color * const getRawDataPtr();



		// data mutators

		/*! Obtains the color of the image at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to get.
		*  \param y is the (zero-based) vertical index of the pixel to get.
		*
		*  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		*/
		Color getPixel(unsigned int x, unsigned int y) const;

		/*! Sets the RGB values for a (x,y) pixel.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to set.
		*  \param y is the (zero-based) vertical index of the pixel to set.
		*  \param value is the new color for the (x,y) pixel.
		*/
		void setPixel(unsigned int x, unsigned int y, Color & value);

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*
		*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const Color * & data_ptr);

		/*! Reads an image file and returns whether it was successful or not
		*
		*	Override operator left shift to read an image file and return whether it has succeded or not.
		*
		*	\param filename is the path of the file to read.
		*/
		bool operator << (std::string filename);

		/*! Outputs an image file and returns whether it was successful or not
		*
		*	Override operator right shift to write the image to a file and return whether it has succeded or not.
		*
		*	\param filename is the path of the file to write to.
		*/
		bool operator >> (std::string filename);

		/*
		class Image also inherits from Array<T> with T=Color
		without overriding these methods:

		unsigned int getWidth() const { return width; }

		unsigned int getHeight() const { return height; }

		T & operator () (int x, int y);

		const T & operator () (int x, int y) const;

		Array<T> & operator = (const Array<T> & source);

		bool operator == (const Array<T> & right) const;

		void resize(unsigned int new_width, unsigned int new_height);

		*/
	};

}

#endif