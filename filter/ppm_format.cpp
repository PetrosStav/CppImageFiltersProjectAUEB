#include <iostream>
#include <fstream>
#include <string>
#include "ppm_format.h"

namespace imaging {	//declares a region that provides a scope to the identifiers and the variables, in order to organize code into logical groups and prevent name collisions

	Image * ReadPPM(const char * filename) {
		std::ifstream file;	//initialize an input file stream
		file.open(filename, std::ios::in | std::ios::binary);	//open file given from arguments in input and binary mode
		if (!file) { //If the file doesn't exist or open
			std::cerr << "ERROR: There was an error opening the image!" << std::endl;
			return nullptr;
		}
		//check header
		std::string token;	//string to obtain the data from the file to check (tokenized)
		file >> token;	//get next token
		while (token.at(0) == '#') {	//first comments -- before P6
			getline(file, token);	//get line after '#' because it is a comment
			file >> token;	//get next token
		}
		int width, height, depth;	//declare image dimensions
		int items = 0;	//variable to check that all dimensions of image are given
		size_t pos = token.find("#"); //find the position of '#' in token
		token = token.substr(0, pos); //clears magic number from comments after P6 using the position above
		if (token.compare("P6") == 0) {	//if token equals "P6"

			while (items != 3) {	//until all the dimensions are read, loop
				file >> token;	//get next token
				while (token.at(0) == '#') { //remove comments -- after P6 & between dimensions
					getline(file, token); //get line after '#' because it is a comment
					file >> token; //get next token
				}
				pos = token.find("#");	//find the position of '#' in token
				token = token.substr(0, pos);	//clears token from comments after the image dimensions 
				int curr;	//declare current int data that will be read
				try {
					curr = std::stoi(token);	//convert token from string to int -- throws invalid argument exception	
					switch (items) {	//check in which dimension to put the data
					case 0:	//width
						width = curr;
						items++; //increment items to go to the next dimension
						break;
					case 1:	//height
						height = curr;
						items++; //increment items to go to the next dimension
						break;
					case 2:	//depth
						depth = curr;
						items++; //increment items to exit the loop
						break;
					}
				}
				catch (std::invalid_argument e) {	//conversion error from stoi
					switch (items) {	//according to the item count find which dimension is missing 
					case 0:
						std::cerr << "ERROR: Image file's width is missing or is invalid!" << std::endl;
						return nullptr;
					case 1:
						std::cerr << "ERROR: Image file's height is missing or is invalid!" << std::endl;
						return nullptr;
					case 2:
						std::cerr << "ERROR: Image file's depth is missing or is invalid!" << std::endl;
						return nullptr;
					}
				}
			}

			while (file.peek() == '#' || file.peek() == ' ' || file.peek() == '\t') { //check for comments after the dimensions
				size_t pos = file.tellg(); //get the position in file
				file >> token; //get next token

							   //if the token size is bigger than 60 (max comment characters) then the token has probably
							   //binary image data so we need to return the the previous position in file, so that we don't
							   //damage the image data
							   //the number 60 is used explicitly because optimaly there won't be a comment that long
				if (token.size() > 60) {
					file.seekg(pos, std::ios::beg);	//goto previous file position held by variable pos
					file.ignore(1);	//ignore exactly 1 character from file
				}
				else { //token is a comment
					getline(file, token); //get the line with the comment
				}
			}

			if (file.peek() == '\n') getline(file, token); //removes the last \n after the image data if it exists

			if (width <= 0 || height <= 0 || depth <= 0 || depth>255) { //check that the dimensions given are correct
				std::cerr << "ERROR: The image file's dimensions are wrong!" << std::endl;
				return nullptr;
			}
		}
		else { //magic number given from token was not equal to "P6"  so it is other than P6 format 
			std::cerr << "ERROR: The image file's magic number is not P6!" << std::endl;
			return nullptr;
		}
		unsigned int size = width*height;	//intialize the size using the dimensions
		Color* buffer = new Color[size];	//allocate the buffer to a component_t array with the size given above
		char bytes[3];	//array of chars used to read the binary values from the file
		for (int i = 0; i < 3*size; i += 3) { //read r,g,b for every pixel and put on data pointer array (buffer)
			file.read(bytes, 3); //read 3 binary values from file
								 //Convert each value of the array bytes from char to unsigned char (so that it has range from 0 to 255)
								 //and then divide it with conponent_t(255) to convert them to component_t (range from 0.0 to 1.0) 
			component_t red = component_t(unsigned char(bytes[0])) / component_t(255);
			component_t green = component_t(unsigned char(bytes[1])) / component_t(255);
			component_t blue = component_t(unsigned char(bytes[2])) / component_t(255);
			buffer[i / 3] = Color(red, green, blue);
		}
		Image* img = new Image(width, height, buffer); //create an image with the data above
		delete[] buffer; //delete buffer used to fill image
		file.close(); //close the file
		return img; //return the image pointer
	}

	bool WritePPM(Image & image, const char * filename) {
		std::ofstream filo;										//initialize an output file stream
		unsigned int width = image.getWidth();					//the width of the image
		unsigned int height = image.getHeight();				//the height of the image
		Color* buffer = image.getRawDataPtr();					//get Image data pointer
		filo.open(filename, std::ios::out | std::ios::binary);	//open file given from arguments in output and binary mode
		if (!filo) {											//if the file fails to open for writing
			std::cerr << "ERROR: There was an error writing the image!" << std::endl;
			return false;
		}
		filo << "P6" << " ";	//write "P6" at the beginning of the output image file
		filo << width << " " << height << " " << "255" << std::endl;	//write the image width, the image height and "255" for depth after "P6"
																		//for each pixel of the image get the pixel Color
																		//convert each value of Color from component_t to unsigned_char (so that it has range from 0 to 255)
																		//and then cast it to char and write it to the output file
		for (int i = 0; i < width*height; i++) {
			filo << char(buffer[i].r * 255) << char(buffer[i].g * 255) << char(buffer[i].b * 255);
		}
		filo.close();	//close the output file stream
		return true;
	}
}