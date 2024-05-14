#pragma once

//#include <optional>	<- shape

//#include <glm.hpp>	<- shape, hit, ray

#include "../core/shape.hpp"
//#include "../core/hit.hpp"	<- shape
//#include "../core/ray.hpp"	<- shape, hit



class Sphere : public Shape {
public:
	float radius;
	Sphere(glm::vec3 position, float radius);
	std::optional<Hit> castRayHook(Ray ray);
};