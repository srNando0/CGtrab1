#pragma once

#include "../core/material.hpp"



class SmoothMaterial : public Material {
/*private:
	glm::vec3 computeColorFromBRDF(
		glm::vec3 view,
		glm::vec3 normal,
		glm::vec3 light
	);*/

public:
	glm::vec3 color;
	float metallic;
	float reflectance;
	
	const float EPSILON = 0.001f;
	
	SmoothMaterial(glm::vec3 color, float metallic, float reflectance);
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};