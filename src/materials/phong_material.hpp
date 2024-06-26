#pragma once

//#include <glm.hpp>

#include "../core/material.hpp"



class PhongMaterial : public Material {
private:
	glm::vec3 computeColorFromBRDF(
		glm::vec3 view,
		glm::vec3 normal,
		glm::vec3 light
	);

public:
	glm::vec3 color;
	float reflectance;
	float shininess;
	
	PhongMaterial(
		glm::vec3 color,
		float reflectance,
		float shininess
	);
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};