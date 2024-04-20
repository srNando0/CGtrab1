#pragma once

#include <vector>

#include "glm.hpp"



class Image {
private:
	const unsigned int mWidth, mHeight;
	
	void createData();
	std::vector<unsigned char> flattenData();

public:
	std::vector<std::vector<glm::vec4>> mData;
	
	Image(unsigned int width, unsigned int height);
	void save(char const *filename);
	
	unsigned int getWidth();
	unsigned int getHeight();
};