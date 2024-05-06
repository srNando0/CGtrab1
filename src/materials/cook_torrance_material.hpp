#pragma once

#include "../core/material.hpp"



class CookTorranceMaterial : public Material {
public:
	CookTorranceMaterial(
		glm::vec3 diffuseColor,
		glm::vec3 specularColor
	);
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};