#pragma once

//#include <glm.hpp>	<- ray

#include "ray.hpp"



class Hit {
public:
	const glm::vec3 origin;
	const glm::vec3 position;
	const glm::vec3 normal;
	const bool isBackfacing;
	
	Hit(
		glm::vec3 origin,
		glm::vec3 position,
		glm::vec3 normal,
		bool isBackfacing
	);
	
	Hit(
		Ray ray,
		float t,
		glm::vec3 normal,
		bool isBackfacing
	);
	
	Ray computeRay();
	Ray computeRayFromPosition(glm::vec3 pos);
	float computeLength();
	float computeSquaredLength();
};