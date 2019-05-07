//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include <iostream>
#include "Array.h"

namespace math
{

	//--------------------------------------------------------------------------------------------
	// This file is included from the templated Array typename header.
	// TODO: Provide its member function implementations here:
	//--------------------------------------------------------------------------------------------

	template <typename T>
	Array<T>::Array(unsigned int w, unsigned int h):width(w),height(h) {	//Constructor with width and height specification
		if (width == 0 || height == 0) {	//if the dimensions passed as parameters are equal to zero
			buffer = nullptr;	//point to nullptr, so that the buffer can't be deleted again causing an access violation
			return;
		}
		buffer = new T[width*height];	//initialize a buffer array of type T and size width*height
		std::memset(buffer, 0, sizeof(T)*width*height);	//fill the new buffer with zeros
	}

	template <typename T>
	Array<T>::Array(const Array<T> & source):width(source.width),height(source.height) {	//Copy constructor
		buffer = new T[width*height];	//initialize a buffer array of type T and size width*height
		std::memcpy(buffer, source.buffer, sizeof(T)*width*height);	//copy each value of source buffer to buffer
	}

	template <typename T>
	Array<T>::~Array() {	//Default constructor
		if (buffer != nullptr) {	//if the image has data, then delete them (free the memory in heap)
			delete[] buffer;
			buffer = nullptr;	//point to nullptr, so that the buffer can't be deleted again causing an access violation
		}
	}

	template <typename T>	
	Array<T> & Array<T>::operator = (const Array<T> & source) {	//Copy assignment operator
		if (&source == this) return *this;	//if the image passed as an argument is the same as the current, return the current one
		width = source.width;	//change the width to the width of the Image passed as an argument
		height = source.height;	//change the height to the height of the Image passed as an argument
		if (buffer != nullptr) {	//makes sure that if there is a previous image, it is deleted
			delete[] buffer;
		}
		buffer = new T[width*height];	//initialize a buffer array of type T and size width*height
		std::memcpy(buffer, source.buffer, sizeof(T)*width*height);	//copy each value of source buffer to buffer
		return *this;	//return the updated image
	}

	template <typename T>
	bool Array<T>::operator == (const Array<T> & right) const {	//equals operator
		if (width != right.width || height != right.height) return false;	//if the dimensions between the two operand Images do not match, return false
		if (std::memcmp(buffer, right.buffer, sizeof(T)*width*height) != 0) return false;	//if the comparison between each pixel of the two operand Images does not return zero as a result, return false
		return true;
	}

	template <typename T>
	T & Array<T>::operator () (int x, int y) {	//Returns a reference to the element at the zero-based position (column x, row y)
		if (x < 0 || y < 0 || x >= width || y >= height) {	//if any of the parameters is out of bounds
			T value = T();	//initialize a value of type T with default constructor
			return value;	//return the default value
		}
		return buffer[y*width + x];	//return the element at position (x,y)
	}

	template <typename T>
	const T & Array<T>::operator () (int x, int y) const {	//Returns a constant reference to the element at the zero-based position (column x, row y)
		if (x < 0 || y < 0 || x >= width || y >= height) {	//if any of the parameters is out of bounds
			T value = T();	//initialize a value of type T with default constructor
			return value;	//return the default value
		}
		return buffer[y*width + x];	//return the element at position (x,y)
	}

	template <typename T>
	void Array<T>::resize(unsigned int new_width, unsigned int new_height) {	//Changes the internal image data storage size
		if (new_width == width && new_height == height) return;	//if the new dimensions are the same as the old, return	
		if (new_width <= 0 || new_height <= 0) return;	//if the new dimensions consist of non-positive values, return
		if (buffer == nullptr) {	//if the Image doesn't have an allocated buffer
			buffer = new T[new_width*new_height];	//initialize a buffer array of type T and size width*height
			std::memset(buffer, 0, sizeof(T)*new_width*new_height);	//fill the new buffer with zeros
		}
		else {	//if the buffer is allocated
			T* new_buffer = new T[new_width*new_height];	//initialize a new buffer array of type T and size new_width*new_height
			for (int i = 0; i < new_height; i++) {	//for each line in the new buffer array
				for (int j = 0; j < new_width; j++) {	//for each column in the new buffer array
					if (i >= height || j >= width) {	//if the dimensions of the new image are larger than the old ones
						new_buffer[i*new_width + j] = T();	//pad the extra values of the new image with black pixels
						continue;	//continue the iteration
					}
					new_buffer[i*new_width + j] = buffer[i*width + j];	//set the index of the old image to the new image 
				}
			}
			//update Image variables
			delete[] buffer;
			buffer = new_buffer;	//allocate the new values to the buffer
		}
		width = new_width;	//update image width
		height = new_height;	//update image height
	}

	template <typename T>
	void * const Array<T>::getRawDataPtr() {	//Obtains a pointer to the internal data
		return buffer;
	}
	

} // namespace math

#endif