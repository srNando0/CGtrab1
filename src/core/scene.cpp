#include "scene.hpp"



/*
	Public Methods
*/
glm::vec4 Scene::traceRay(Ray ray) {
	return glm::vec4(1.0, 0.0, 0.0, 1.0);
}



Hit Scene::computeIntersection(Ray ray) {
	glm::vec4 a;
	return Hit(a, a, a, false, nullptr);
}