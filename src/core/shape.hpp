#pragma once

#include <optional>

//#include <glm.hpp>	<- hit, ray

//#include "ray.hpp"	<- hit
#include "hit.hpp"



class Shape {
public:
	glm::vec3 position;
	glm::mat4 matrix;
	
	virtual ~Shape();
	virtual std::optional<Hit> castRay(Ray ray) = 0;
};