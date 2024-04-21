#pragma once

#include <vector>

#include "glm.hpp"



class Image {
private:
	void createData();
	std::vector<unsigned char> flattenData();

public:
	const unsigned int mWidth, mHeight;
	
	std::vector<std::vector<glm::vec4>> mData;
	
	Image(unsigned int width, unsigned int height);
	void save(char const *filename);
};