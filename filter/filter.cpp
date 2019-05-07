#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ppm_format.h"
#include "GrayFilter.h"
#include "ColorFilter.h"
#include "BlurFilter.h"
#include "MedianFilter.h"
#include "DiffFilter.h"

using namespace std;

int main(int argc, char* argv[]) {

	string fileName;	//the path of the image file to load
	string outName;		//the path of the image file to output
	if (argc < 4) {		//if the user didn't put argument for file name or filters, print error message and exit
		cerr << "No file name or filters!\nUsage: filter.exe -f [filter 1] -f [filter 2] ... -f [filter k] [file path].ppm\n";
		system("pause");
		return -1;
	}

	fileName = argv[argc - 1];					//the image filename is the last argument, at position (argc-1), since we begin counting from zero
	imaging::Image* img = new imaging::Image();	//create a default image
	if (!(*img << fileName.c_str())) {			//read file to img, if not successful exit	
		system("pause");
		return -1;
	}

	cout << fileName << endl;				//display file path
	unsigned int width = img->getWidth();	//get width from Image
	unsigned int height = img->getHeight();	//get height from Image
	cout << "Image dimensions are: " << width << " X " << height << endl;	//display Image dimensions
	
	//make a vector of Filter* so that we can use polymorphism to apply all the filters
	std::vector<imaging::Filter*> filters;

	//check that the arguments given are all valid
	int i = 1;										//initialize a counter
	while (i < argc-1) {							//while there are arguments
		if (strcmp("-f", argv[i])==0) {				//if the first argument equals to "-f"
			if (strcmp("gray", argv[i + 1]) == 0) {	//if the second argument equals to "gray"
				filters.push_back(new imaging::GrayFilter(img));	//push a GrayFilter object to the vector
				i += 2;												//go to the next argument
			}else if (strcmp("color", argv[i + 1]) == 0) {			//if the second argument equals to "color"
				try {
					//check that after the color filter there are 3 valid values
					//stod is used instead of atof, because atof returns 0.0 if it has encountered an error
					//which doesn't suit our situation
					imaging::component_t red = (imaging::component_t)std::stod(argv[i+2]);
					imaging::component_t green = (imaging::component_t)std::stod(argv[i + 3]);
					imaging::component_t blue = (imaging::component_t)std::stod(argv[i + 4]);

					filters.push_back(new imaging::ColorFilter(img, imaging::Color(red, green, blue)));	//QQ
					i += 5;	//go to the next argument
				}
				catch (invalid_argument ia) {
					cerr << "Invalid arguments for color_filter!\n";
					system("pause");	
					delete img;		
					return -1;
				}
				catch (out_of_range oor) {
					cerr << "Color arguments are out of bounds!\n";
					system("pause");
					delete img;
					return -1;
				}
			}
			else if (strcmp("blur", argv[i + 1]) == 0) {			//if the second argument equals to "blur"
				filters.push_back(new imaging::BlurFilter(img));	//push a BlurFilter object to the vector
				i += 2;
			}
			else if (strcmp("median", argv[i + 1]) == 0) {			//if the second argument equals to "median"
				filters.push_back(new imaging::MedianFilter(img));	//push a MedianFilter object to the vector
				i += 2;
			}
			else if (strcmp("diff", argv[i + 1]) == 0) {			//if the second argument equals to "diff"
				filters.push_back(new imaging::DiffFilter(img));	//push a DiffFilter object to the vector
				i += 2;
			}
			else {	//if the second argument does not equal any of the above
				cerr << "There is no filter: " << argv[i + 1] << "!\nAvailable filters are: gray, color, blur, diff, median.\n";
				system("pause");
				delete img;
				return -1;
			}
		}
		else {	//if the first argument does not equal to "-f"
			cerr << "Invalid tags!\nUsage: filter.exe -f [filter 1] -f [filter 2] ... -f [filter k] [file path].ppm\n";
			system("pause");
			delete img;
			return -1;
		}
	}

	//iterate through the vector and call the apply_filter() method to all Filter objects using polymorphism

	for (std::vector<imaging::Filter*>::iterator it = filters.begin(); it != filters.end(); ++it) {
		cout << "Applying " << typeid(*(*it)).name()+15 << "..." << endl;			//output the Filter name that is currently being applied
		(*it)->apply_filter();														//apply the filter to the image
		delete (*it);																//delete the Filter object to free the memory it is using
	}
	
	outName = fileName.substr(0, fileName.length() - 4).append(".filtered.ppm");	//add ".filtered.ppm" to the end of the filename of the image
	if (*img>>outName.c_str()) {													//if the output image was created successfully
		cout << "Image written to " << outName << endl;
	}
	delete img;			//delete img before we close the program

	system("pause");
	return 0;
}