#include "scene.hpp"



/*
	Constructor and Destructor
*/
Scene::Scene(
	glm::vec4 ambientColor,
	glm::vec4 skyColor
) : ambientColor(ambientColor), skyColor(skyColor) {}



/*
	Public Methods
*/
glm::vec4 Scene::traceRay(Ray ray, unsigned int recursion) {
	std::optional<Collision> collision = castRay(ray);
	if (collision) {
		Hit hit = collision->hit;
		std::shared_ptr<Material> material = collision->instance->material;
		return material->computeColor(hit, *this, recursion);
	} else {
		return getSky(ray);
	}
}



std::optional<Collision> Scene::castRay(Ray ray) {
	std::optional<Hit> nearestHit;
	std::optional<std::shared_ptr<Instance>> nearestInstance;
	
	for (auto& instance : instances) {
		std::optional<Hit> hit = instance->shape->castRay(ray);
		if (hit) {
			if (nearestHit) {
				if (hit->computeLength() < nearestHit->computeLength()) {
					nearestHit.emplace(hit.value());
					nearestInstance.emplace(instance);
				}
			} else {
				nearestHit.emplace(hit.value());
				nearestInstance.emplace(instance);
			}
		}
	}
	
	if (nearestHit)
		return Collision(nearestHit.value(), nearestInstance.value());
	else
		return {};
}



glm::vec4 Scene::getAmbient(Ray ray) {
	return ambientColor;
}



glm::vec4 Scene::getSky(Ray ray) {
	return skyColor;
}