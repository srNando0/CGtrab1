#pragma once

#include <optional>

//#include <glm.hpp>	<- hit, ray

//#include "ray.hpp"	<- hit
#include "hit.hpp"



class Shape {
public:
	glm::vec3 position;
	glm::mat3 matrix;
	
	Shape(glm::vec3 position);
	virtual ~Shape();
	virtual std::optional<Hit> castRayHook(Ray ray) = 0;
	std::optional<Hit> castRay(Ray ray);
};