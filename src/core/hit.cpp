#include "hit.hpp"



/*
	Constructor and Destructor
*/
Hit::Hit(
	glm::vec3 origin,
	glm::vec3 position,
	glm::vec3 normal,
	bool isBackfacing
) : origin(origin), position(position), normal(glm::normalize(normal)), isBackfacing(isBackfacing) {}

Hit::Hit(
	Ray ray,
	float t,
	glm::vec3 normal,
	bool isBackfacing
) : origin(ray.origin), position(ray.origin + t*ray.dir), normal(glm::normalize(normal)), isBackfacing(isBackfacing) {}



/*
	Public Methods
*/
Ray Hit::computeRay() {
	return Ray(position, origin - position);
}

Ray Hit::computeRayFromPosition(glm::vec3 pos) {
	return Ray(position, pos - position);
}



float Hit::computeLength() {
	return glm::length(position - origin);
}

float Hit::computeSquaredLength() {
	return glm::dot(position - origin, position - origin);
}