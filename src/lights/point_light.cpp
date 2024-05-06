#include "point_light.hpp"



/*
	Constructor and Destructor
*/
PointLight::PointLight(
	glm::vec3 color,
	std::shared_ptr<Sphere> sphere,
	Scene& scene
) : instance(
	std::make_shared<Instance>(
		sphere,
		std::make_shared<EmissiveMaterial>(color)
	)
), color(color) {
	scene.instances.push_back(instance);
}



/*
	Public Methods
*/
std::vector<LightRay> PointLight::computeLightRays(Hit hit, Scene& scene, unsigned int recursion) {
	glm::vec3 position = instance->shape->position;
	glm::vec3 dir = glm::normalize(position - hit.position);
	float sqrDistance = glm::dot(position - hit.position, position - hit.position);
	
	Ray ray(hit.position + EPSILON*dir, dir);
	std::optional<Collision> collision = scene.castRay(ray);
	
	if (collision) {
		if (collision->instance == instance) {
			return {LightRay(color/sqrDistance, dir)};
		} else {
			return {};
		}
	} else {
		return {LightRay(color/sqrDistance, dir)};
	}
}