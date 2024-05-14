#include "shape.hpp"



/*
	Constructor and Destructor
*/
Shape::Shape(glm::vec3 position) : position(position), matrix(glm::mat3x3(1.0f)) {}
Shape::~Shape() {}



/*
	Public Methods
*/
std::optional<Hit> Shape::castRay(Ray ray) {
	glm::vec3 distance = ray.origin - position;
	glm::mat3 invMat = glm::inverse(matrix);
	Ray newRay(
		invMat*distance + position,
		invMat*ray.dir
	);
	
	std::optional<Hit> opHit = castRayHook(newRay);
	
	if (opHit) {
		distance = opHit->position - position;
		return Hit(
			ray.origin,
			matrix*distance + position,
			glm::transpose(invMat)*opHit->normal,
			opHit->isBackfacing
		);
	} else {
		return {};
	}
}