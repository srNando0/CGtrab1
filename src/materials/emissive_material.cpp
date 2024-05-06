#include "emissive_material.hpp"



/*
	Constructor and Destructor
*/
EmissiveMaterial::EmissiveMaterial(glm::vec3 color) : color(color) {}



/*
	Public Methods
*/
glm::vec4 EmissiveMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	return glm::vec4(color/hit.computeSquaredLength(),1.0f);
}