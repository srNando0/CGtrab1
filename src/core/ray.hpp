#pragma once

#include <glm.hpp>



class Ray {
public:
	const glm::vec3 origin;
	const glm::vec3 dir;
	
	Ray(glm::vec3 origin, glm::vec3 dir);
	Ray(Ray ray, float t);
};