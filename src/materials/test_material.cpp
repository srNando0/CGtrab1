#include "test_material.hpp"



/*
	Public Methods
*/
glm::vec4 TestMaterial::computeColor(Hit hit, Scene& scene, unsigned int recursion) {
	return glm::vec4((hit.normal + glm::vec3(1.0f, 1.0f, 1.0f))/2.0f, 1.0f);
}