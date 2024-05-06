#include "phong_material.hpp"

#include <cmath>

#include "functions/material_functions.hpp"

//#include <glm.hpp>



/*
	Constructor and Destructor
*/
PhongMaterial::PhongMaterial(
	glm::vec3 diffuseColor,
	glm::vec3 specularColor,
	float shininess
) : diffuseColor(diffuseColor), specularColor(specularColor), shininess(shininess) {}



/*
	Public Methods
*/
glm::vec4 PhongMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	glm::vec3 color(0.0f, 0.0f, 0.0f);
	
	for (const auto& light : scene.lights) {
		std::vector<LightRay> lightRays = light->computeLightRays(hit, scene, recursion);
		
		for (const auto& lightRay : lightRays) {
			color += material::phong(
				hit.computeRay().dir,
				hit.isBackfacing ? -hit.normal : hit.normal,
				lightRay.dir,
				specularColor*lightRay.color,
				shininess
			);
		}
	}
	
	color = color/hit.computeSquaredLength() + diffuseColor*glm::vec3(
		scene.getAmbient(hit.computeRay())
	);
	
	return glm::vec4(color, 1.0f);
}