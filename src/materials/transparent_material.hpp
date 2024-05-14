#pragma once

#include "../core/material.hpp"



class TransparentMaterial : public Material {
private:
	glm::vec3 refract(glm::vec3 direction, glm::vec3 normal, float ratio);
public:
	glm::vec3 color;
	float refractionRatio;
	
	const float EPSILON = 0.001f;
	
	TransparentMaterial(glm::vec3 color, float refractionRatio);
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};