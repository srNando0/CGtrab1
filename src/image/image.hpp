/*
PUBLIC ATTRIBUTES:
	width - literally the image width
	height - literally the image height
	data - a 2D vector of glm::vec4 as RGBA colors



CONSTRUCTOR:
	Image(unsigned int width, unsigned int height)
	
	DESCRIPTION:
		Initializes data where data[i][j] is the pixel in the i-th position
		from left to right and in the j-th position from top to bottom.



PUBLIC METHOD:
	void save(const char* filename)
	
	DESCRIPTION:
		Saves a png image in the location given by the input "filename"



USAGE:
	First, create an object giving its resolution.
	E.g.:
		Image image(640, 480);
	
	Use the "data" attribute to read and write any color at any pixel.
	The brackets notation "data[i][j]" accesses the pixel color in the i-th
	position from left to right and in the j-th position from top to bottom.
	The color type at any pixel in "data[i][j]" is glm::vec4.
	E.g.:
		glm::vec4 pixelColor = image.data[100][200];
		image.data[image.width/2][image.height/2] = glm::vec4(1.0, 0.0, 0.0, 1.0);
	
	To save the image as png, use "save" method.
	E.g.:
		image.save("frenchFlag.png");
*/



#pragma once

#include <vector>

#include <glm.hpp>



class Image {
private:
	void createData();
	std::vector<unsigned char> flattenData();

public:
	const unsigned int width, height;
	
	std::vector<std::vector<glm::vec4>> data;
	
	Image(unsigned int width, unsigned int height);
	void save(const char* filename);
};