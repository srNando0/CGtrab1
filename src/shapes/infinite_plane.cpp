#include "infinite_plane.hpp"



/*
	Constructor and Destructor
*/
InfinitePlane::InfinitePlane(
	glm::vec3 position,
	glm::vec3 normal
) : Shape(position), normal(glm::normalize(normal)) {}



/*
	Public Methods
*/
std::optional<Hit> InfinitePlane::castRayHook(Ray ray) {
	/*
		n'(x - p) = 0
		x = o + td
		n'(o + td - p) = 0
		n'(o - p) + tn'd = 0
		tn'd = n'(p - o)
		t = n'(p - o)/(n'd)
		x = o + (n'(p - o)/(n'd))d
		
		backface <=> n'(o - p) < 0
		backface <=> 0 < n'(p - o)
	*/
	float numerator = glm::dot(normal, position - ray.origin);
	float denominator = glm::dot(normal, ray.dir);
	
	if (denominator == 0.0f)
		return {};
	
	float t = numerator/denominator;
	
	if (t < 0.0f) {
		return {};
	} else {
		return Hit(
			ray,
			t,
			normal,
			0 < numerator
		);
	}
}