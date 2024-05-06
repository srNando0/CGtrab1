#pragma once

//#include <glm.hpp>

#include "../core/material.hpp"



class PhongMaterial : public Material {
public:
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	
	float specularRate;
	float shininess;
	
	PhongMaterial(
		glm::vec3 diffuseColor,
		glm::vec3 specularColor,
		float shininess)
	;
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};