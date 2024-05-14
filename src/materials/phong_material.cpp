#include "phong_material.hpp"

#include "functions/material_functions.hpp"

#define PI (float) 3.141592653589793115997963468544185161590576171875

//#include <glm.hpp>



/*
	Constructor and Destructor
*/
PhongMaterial::PhongMaterial(
	glm::vec3 color,
	float reflectance,
	float shininess
) : PhongMaterial::Material(false), color(color), reflectance(reflectance), shininess(shininess) {}



/*
	Private Methods
*/
glm::vec3 PhongMaterial::computeColorFromBRDF(
	glm::vec3 view,
	glm::vec3 normal,
	glm::vec3 light
) {
	float p = material::phong(
		light,
		normal,
		view,
		shininess
	);
	
	glm::vec3 diffuse = color/PI;
	glm::vec3 specular = p*glm::vec3(1.0f);
	
	return (1.0f - reflectance)*diffuse + reflectance*specular;
}



/*
	Public Methods
*/
glm::vec4 PhongMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	if (scene.maxRecursion < recursion)
		return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	glm::vec3 colorSum = (1.0f - reflectance)*color*glm::vec3(
		scene.getAmbient(hit.computeRay())
	);
	
	glm::vec3 view = hit.computeRay().dir;
	glm::vec3 normal = hit.isBackfacing ? -hit.normal : hit.normal;
	
	for (const auto& light : scene.lights) {
		std::vector<LightRay> lightRays = light->computeLightRays(hit, scene, recursion);
		
		for (const auto& lightRay : lightRays) {
			glm::vec3 light = lightRay.dir;
			float cosine = glm::dot(light, normal);
			glm::vec3 radiance = lightRay.color;
			glm::vec3 brdf = computeColorFromBRDF(
				view,
				normal,
				light
			);
			
			colorSum += PI*radiance*brdf*cosine;
		}
	}
	
	return glm::vec4(colorSum, 1.0f);
}