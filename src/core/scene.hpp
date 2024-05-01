#pragma once

#include <vector>

#include <glm.hpp>

#include "instance.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "hit.hpp"



class Scene {
public:
	std::vector<Instance> instances;
	std::vector<Light> lights;
	
	glm::vec4 traceRay(Ray ray);
	Hit computeIntersection(Ray ray);
};