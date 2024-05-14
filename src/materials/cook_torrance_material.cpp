#include "cook_torrance_material.hpp"

#include "functions/material_functions.hpp"

//#include <glm.hpp>

#define PI (float) 3.141592653589793115997963468544185161590576171875



/*
	Constructor and Destructor
*/
CookTorranceMaterial::CookTorranceMaterial(
	glm::vec3 color,
	float roughness,
	float metallic
) : CookTorranceMaterial::Material(false), color(color), roughness(roughness), metallic(metallic) {}



/*
	Private Methods
*/
glm::vec3 CookTorranceMaterial::computeColorFromBRDF(
	glm::vec3 view,
	glm::vec3 normal,
	glm::vec3 light
) {
	glm::vec half = glm::normalize(light + view);
	float nh = glm::dot(normal, half);
	float hv = glm::dot(half, view);
	
	float alpha = roughness*roughness;
	float d = material::ggxD(nh, alpha);
	float v = material::ggxV(light, normal, view, alpha);
	
	glm::vec3 c = glm::mix(glm::vec3(1.0f), color, metallic);
	glm::vec3 fresnel = material::fresnel(c, hv);
	glm::vec3 specular = d*v*fresnel;
	glm::vec3 diffuse = (glm::vec3(1.0f) - fresnel)*(1.0f - metallic)*color/PI;

	return diffuse + specular;
}



/*
	Public Methods
*/
glm::vec4 CookTorranceMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	if (scene.maxRecursion < recursion)
		return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	glm::vec3 colorSum(0.0f, 0.0f, 0.0f);
	glm::vec3 view = hit.computeRay().dir;
	glm::vec3 normal = hit.isBackfacing ? -hit.normal : hit.normal;
	
	// for lights
	for (const auto& light : scene.lights) {
		std::vector<LightRay> lightRays = light->computeLightRays(hit, scene, recursion);
		
		for (const auto& lightRay : lightRays) {
			glm::vec3 light = lightRay.dir;
			float cosine = glm::dot(light, normal);
			glm::vec3 radiance = lightRay.color;
			glm::vec3 brdf = computeColorFromBRDF(
				light,
				normal,
				view
			);
			
			colorSum += PI*radiance*brdf*cosine;
		}
	}
	
	// for reflection
	/*glm::vec3 light = -glm::reflect(view, normal);
	
	Ray ray(hit.position + EPSILON*light, light);
	glm::vec4 reflectionColor = scene.traceRay(ray, recursion + 1);
	
	float cosine = glm::dot(light, normal);
	glm::vec3 radiance = glm::vec3(reflectionColor);
	glm::vec3 brdf = glm::clamp(computeColorFromBRDF(
		light,
		normal,
		view
	), 0.0f, 100.0f);
	
	color += PI*radiance*brdf*cosine;*/
	
	// final color
	colorSum += color*glm::vec3(
		scene.getAmbient(hit.computeRay())
	);
	
	return glm::vec4(colorSum, 1.0f);
}