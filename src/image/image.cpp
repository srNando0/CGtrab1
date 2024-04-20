#include "image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



/*
	Constructor and Destructor
*/
Image::Image(unsigned int width, unsigned int height) : mWidth(width), mHeight(height) {
	createData();
}



/*
	Private Methods
*/
void Image::createData() {
	mData = std::vector<std::vector<glm::vec4>>(
		mWidth,
		std::vector<glm::vec4>(
			mHeight,
			glm::vec4(0.0)
		)
	);
}



std::vector<unsigned char> Image::flattenData() {
	std::vector<unsigned char> flattenedData;
	
	for (const auto& column : mData) {
		for (const auto& pixel : column) {
			glm::vec4 pixel255 = 255.0f*pixel;
			
			flattenedData.push_back(static_cast<unsigned char>(pixel255.r));
			flattenedData.push_back(static_cast<unsigned char>(pixel255.g));
			flattenedData.push_back(static_cast<unsigned char>(pixel255.b));
			flattenedData.push_back(static_cast<unsigned char>(pixel255.a));
			//flattenedData.insert(flattenedData.end(), pixel.begin(), pixel.end());
		}
	}
	
	return flattenedData;
}



/*
	Public Methods
*/
void Image::save(char const *filename) {
	stbi_write_png(filename, mWidth, mHeight, 4, flattenData().data(), 4*mWidth);
}



/*
	Getters and Setters
*/
unsigned int Image::getWidth() {
	return mWidth;
}

unsigned int Image::getHeight() {
	return mHeight;
}