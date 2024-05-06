#pragma once

//#include <vector>		<- scene

#include "light_ray.hpp"
#include "scene.hpp"



class Scene;

class Light {
public:
	virtual ~Light();
	virtual std::vector<LightRay> computeLightRays(Hit hit, Scene& scene, unsigned int recursion) = 0;
};