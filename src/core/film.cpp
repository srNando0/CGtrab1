#include "film.hpp"



/*
	Constructor and Destructor
*/
Film::Film(glm::vec2 resolution, unsigned int spp) : resolution(resolution), spp(spp),
mImage(static_cast<unsigned int>(resolution.x), static_cast<unsigned int>(resolution.y)) {}



/*
	Public Methods
*/
float Film::computeRatio() {
	return resolution.x/resolution.y;
}

void Film::saveImage(const char* filename) {
	mImage.save(filename);
}



/*
	Getters and Setters
*/
glm::vec2 Film::getColor(unsigned int i, unsigned int j) {
	return mImage.data[i][j];
}

void Film::setColor(unsigned int i, unsigned int j, glm::vec4 color) {
	mImage.data[i][j] = glm::clamp(color, 0.0f, 1.0f);
}