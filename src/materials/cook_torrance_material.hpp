#pragma once

#include "../core/material.hpp"



class CookTorranceMaterial : public Material {
private:
	glm::vec3 computeColorFromBRDF(
		glm::vec3 view,
		glm::vec3 normal,
		glm::vec3 light
	);

public:
	glm::vec3 color;
	float roughness;
	float metallic;
	
	const float EPSILON = 0.001f;
	
	CookTorranceMaterial(
		glm::vec3 color,
		float roughness,
		float metallic
	);
	
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};