#include "point_light.hpp"

#include "../materials/transparent_material.hpp"



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
		std::make_shared<EmissiveMaterial>(color/sphere->radius)
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
	
	glm::vec3 lightColor(color);
	//glm::vec3 lightColor(glm::vec3(1.0f, 0.0f, 1.0f));
	Ray ray(hit.position + EPSILON*dir, dir);
	std::optional<Collision> collision = scene.castRay(ray);
	
	while (collision) {
		if (collision->instance == instance) {
			// light
			return {LightRay(lightColor/sqrDistance, dir)};
		} else {
			// not light
			if (collision->instance->material->mIsTransparent) {
				// transparent
				if (collision->hit.isBackfacing) {
					// out transparent
					std::shared_ptr<TransparentMaterial> transparent(
						std::static_pointer_cast<TransparentMaterial>(collision->instance->material)
					);
					float length = glm::length(collision->hit.position - collision->hit.origin);
					lightColor *= glm::exp(-transparent->color*length);
				}
			} else {
				// opaque
				return {};
			}
		}
		
		// new ray tracing
		Ray newRay(collision->hit.position + EPSILON*dir, dir);
		std::optional<Collision> newCollision = scene.castRay(newRay);
		
		if (newCollision) {
			collision.emplace(newCollision.value());
		} else {
			collision.reset();
		}
	}
	
	// sky
	return {LightRay(lightColor/sqrDistance, dir)};
}