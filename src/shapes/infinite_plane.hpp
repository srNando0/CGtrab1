#pragma once

#include "../core/shape.hpp"



class InfinitePlane : public Shape {
public:
	glm::vec3 normal;
	
	InfinitePlane(glm::vec3 position, glm::vec3 normal);
	std::optional<Hit> castRayHook(Ray ray);
};