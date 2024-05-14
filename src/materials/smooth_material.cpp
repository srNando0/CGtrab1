#include "smooth_material.hpp"

#include "functions/material_functions.hpp"

#define PI (float) 3.141592653589793115997963468544185161590576171875



/*
	Constructor and Destructor
*/
SmoothMaterial::SmoothMaterial(
	glm::vec3 color,
	float metallic,
	float reflectance
) : SmoothMaterial::Material(false), color(color), metallic(metallic), reflectance(reflectance) {}



/*
	Private Methods
*/
/*glm::vec3 SmoothMaterial::computeColorFromBRDF(
	glm::vec3 view,
	glm::vec3 normal,
	glm::vec3 light
) {
	float nl = glm::dot(normal, light);
	glm::vec3 c = glm::mix(glm::vec3(1.0f), color, metallic);
	
	glm::vec3 fresnel = material::fresnel(c, nl);
	
	glm::vec3 specular = fresnel;
	glm::vec3 diffuse = (glm::vec3(1.0f) - fresnel)*(1.0f - metallic)*color/PI;

	return diffuse + specular;
}*/



/*
	Public Methods
*/
glm::vec4 SmoothMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	if (scene.maxRecursion < recursion)
		return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	glm::vec3 view = hit.computeRay().dir;
	glm::vec3 normal = hit.isBackfacing ? -hit.normal : hit.normal;
	
	// for lights
	glm::vec3 diffusion(0.0f);
	for (const auto& light : scene.lights) {
		std::vector<LightRay> lightRays = light->computeLightRays(hit, scene, recursion);
		
		for (const auto& lightRay : lightRays) {
			glm::vec3 light = lightRay.dir;
			float cosine = glm::dot(light, normal);
			glm::vec3 radiance = lightRay.color;
			
			diffusion += PI*radiance*cosine;
		}
	}
	diffusion *= color;
	
	// for reflection
	glm::vec3 light = -glm::reflect(view, normal);
	
	Ray ray(hit.position + EPSILON*light, light);
	glm::vec4 reflectionColor = scene.traceRay(ray, recursion + 1);
	glm::vec3 specular = glm::vec3(reflectionColor);
	
	// fresnel
	float nl = glm::dot(normal, light);
	glm::vec3 c = glm::mix(glm::vec3(1.0f), color, metallic);
	glm::vec3 fresnel = material::fresnel(reflectance*c, nl);
	
	specular *= fresnel;
	diffusion *= (1.0f - metallic)*(glm::vec3(1.0f) - fresnel);
	
	glm::vec3 colorSum = diffusion + specular;
	
	// final color
	colorSum += (1.0f - reflectance)*color*glm::vec3(
		scene.getAmbient(hit.computeRay())
	);
	
	return glm::vec4(colorSum, 1.0f);
}