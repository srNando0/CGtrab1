#include "sphere.hpp"

#include <cmath>
#include <iostream>



/*
	Constructor and Destructor
*/
Sphere::Sphere(glm::vec3 position, float radius) : Shape(position), radius(radius) {}



/*
	Public Methods
*/
std::optional<Hit> Sphere::castRayHook(Ray ray) {
	/*
		Math:
		
		Sphere:
		(x - c)'(x - c) = r^2
		x = o + td
		m = o - c
		t^2 + 2d'mt + m'm = r^2
		
		Algebra:
		t^2 + 2bt + c = 0
		t = -b +- sqrt(b^2 - c)
		D = b^2 - c
		D = (d'm)^2 - m'm + r^2
	*/
	glm::vec3 m = ray.origin - position;
	float b = glm::dot(ray.dir, m);
	float c = glm::dot(m, m) - radius*radius;
	float discriminant = b*b - c;
	
	// no collision
	if (discriminant < 0.0f)
		return {};
	
	float sqrt = sqrtf(discriminant);	// guaranteed to be valid
	float tp = -b + sqrt;
	if (tp < 0.0f)						// solution point behind ray
		return {};
	
	// collision: 0 <= tp is guaranteed
	float tm = -b - sqrt;
	glm::vec3 hitPoint;
	float isBackfacing;
	
	if (tm < 0.0f) {	// back-face
		isBackfacing = true;
		hitPoint = ray.origin + tp*ray.dir;
	} else {			// front-face
		isBackfacing = false;
		hitPoint = ray.origin + tm*ray.dir;
	}
	
	return Hit(
		ray.origin,
		hitPoint,
		hitPoint - position,
		isBackfacing
	);
}