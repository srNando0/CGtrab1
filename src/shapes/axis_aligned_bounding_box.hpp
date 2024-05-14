#pragma once

#include "../core/shape.hpp"



class AxisAlignedBoundingBox : public Shape {
public:
	glm::vec3 dimensions;
	
	AxisAlignedBoundingBox(glm::vec3 position, glm::vec3 dimentions);
	std::optional<Hit> castRayHook(Ray ray);
};