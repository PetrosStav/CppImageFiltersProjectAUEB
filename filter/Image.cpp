#include "Image.h"
#include "ppm_format.h"


namespace imaging {

	Image::Image() : math::Array<Color>(0, 0) {}	//Default constructor, uses math::Array constructor

	Image::Image(unsigned int w, unsigned int h) : math::Array<Color>(w, h) {}	//Constructor with width and height specification, uses math::Array constructor

	Image::Image(unsigned int width, unsigned int height, const Color * data_ptr): math::Array<Color>(width,height) {	//Constructor with data initialization, uses math::Array constructor
		setData(data_ptr);	//copy the contents of data_ptr to buffer using the setData method
	}

	Image::Image(const Image & source): math::Array<Color>(source) {}	//Copy constructor, uses math::Array copy constructor

	Image::~Image() {				//The Image destructor
		if (buffer != nullptr) {	//if the image has data, then delete them (free the memory in heap)
			delete[] buffer;
			buffer = nullptr;		//point to nullptr, so that the buffer can't be deleted again causing an access violation
		}
	}

	Color* const Image::getRawDataPtr() {	//Obtains a pointer to the internal data, overriding the void* method so that the user doesn't have to do it everytime an internal pointer is needed
		return buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const{	//Obtains the Color of the image at pixel location (x,y)
		return (*this)(x,y);										
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value){	//Sets the Color value for pixel (x,y) in the Image to value
		(*this)(x, y) = value;
	}

	void Image::setData(const Color *& data_ptr){						//Copies the image data from an external raw buffer to the internal image buffer	
		if (buffer == nullptr || width == 0 || height == 0) return;		//if the buffer is set to nullptr or the image dimensions are 0, return
		std::memcpy(buffer, data_ptr, sizeof(Color) * height * width);	//copy each value of src.buffer to buffer
	}

	bool Image::operator<<(std::string filename)	//left shift operator
	{
		Image* tmp = ReadPPM(filename.c_str());		//read image named "filename" and assign it to tmp
		if (tmp != nullptr) {						//if tmp is not nullptr (image was read successfully from file)
			*this = *tmp;							//use operator = method of Image to copy tmp data to this
			delete tmp;								//free the memory
			return true;							//the image file has been read
		}
		else {
			return false;							//the image file has not been read
		}
	}

	bool Image::operator >> (std::string filename)	//right shift operator
	{
		return WritePPM(*this,filename.c_str());	//write this Image to a file named "filename" and return true if it completed successfully
	}

}