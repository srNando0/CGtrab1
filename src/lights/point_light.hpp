#pragma once

//#include <glm.hpp>		<- scene, light, light_ray

#include "../core/scene.hpp"
//#include "../core/light.hpp"		<- scene
//#include "../core/light_ray.hpp"	<- scene, light
//#include "../core/instance.hpp"	<- scene, collision

#include "../shapes/sphere.hpp"

#include "../materials/emissive_material.hpp"




class PointLight : public Light {
public:
	glm::vec3 color;
	const std::shared_ptr<Instance> instance;
	
	const float EPSILON = 0.001f;
	
	PointLight(glm::vec3 color, std::shared_ptr<Sphere> sphere, Scene& scene);
	
	std::vector<LightRay> computeLightRays(Hit hit, Scene& scene, unsigned int recursion);
};