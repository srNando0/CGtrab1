#pragma once

#include "../core/material.hpp"



class EmissiveMaterial : public Material {
public:
	glm::vec3 color;
	
	EmissiveMaterial(glm::vec3 color);
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};