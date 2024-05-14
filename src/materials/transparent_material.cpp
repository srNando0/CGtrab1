#include "transparent_material.hpp"

#include "functions/material_functions.hpp"

#define PI (float) 3.141592653589793115997963468544185161590576171875



/*
	Constructor and Destructor
*/
TransparentMaterial::TransparentMaterial(
	glm::vec3 color,
	float refractionRatio
) : TransparentMaterial::Material(true), color(color), refractionRatio(glm::max(0.00000001f, refractionRatio)) {}



/*
	Private Methods
*/
glm::vec3 TransparentMaterial::refract(glm::vec3 direction, glm::vec3 normal, float ratio) {
	glm::vec3 d = glm::normalize(direction);
	glm::vec3 n = glm::normalize(normal);
	float c = -glm::dot(n, d);
	float k = 1.0f - ratio*ratio*(1.0f - c*c);
	if (k < 0.0f)
		return d + 2.0f*c*n;
	else
		return ratio*d + (ratio*c - glm::sqrt(k))*n;
}



/*
	Public Methods
*/
glm::vec4 TransparentMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	if (scene.maxRecursion < recursion)
		return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	if (hit.isBackfacing) {
		// inside case
		glm::vec3 direction = refract(
			hit.position - hit.origin,
			-hit.normal,
			1.0f/refractionRatio
		);/*
		direction = refract(
			direction,
			-hit.normal,
			1.0f/refractionRatio
		);*/
		Ray ray(hit.position + EPSILON*direction, direction);
		glm::vec4 beerLambert(glm::exp(-color*hit.computeLength()), 1.0f);
		
		return beerLambert*scene.traceRay(ray, recursion + 1);
		
		
		
	} else {
		// outside case
		glm::vec3 view = glm::normalize(hit.origin - hit.position);
		glm::vec3 normal = hit.normal;
		
		// for reflection
		glm::vec3 light = -glm::reflect(view, normal);
		
		Ray reflectionRay(hit.position + EPSILON*light, light);
		glm::vec3 reflectionColor(scene.traceRay(reflectionRay, recursion + 1));
		
		// for refraction
		glm::vec3 direction = refract(
			hit.position - hit.origin,
			hit.normal,
			refractionRatio
		);/*
		direction = refract(
			direction,
			hit.normal,
			1.0f/refractionRatio
		);*/
		Ray refractionRay(hit.position + EPSILON*direction, direction);
		glm::vec3 refractionColor(scene.traceRay(refractionRay, recursion));
		
		// fresnel
		float nl = glm::dot(normal, light);
		glm::vec3 fresnel = material::fresnel(glm::vec3(0.0f), nl);
		
		glm::vec3 colorSum = (glm::vec3(1.0f) - fresnel)*refractionColor + fresnel*reflectionColor;
		
		// final color
		return glm::vec4(colorSum, 1.0f);
	}
}