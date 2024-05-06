#pragma once

//#include <glm.hpp>	<- image

#include "../image/image.hpp"



class Film {
private:
	Image mImage;

public:
	const glm::vec2 resolution;
	const unsigned int spp;
	
	Film(glm::vec2 resolution, unsigned int spp);
	float computeRatio();
	void saveImage(const char* filename);
	
	glm::vec2 getColor(unsigned int i, unsigned int j);
	void setColor(unsigned int i, unsigned int j, glm::vec4 color);
};