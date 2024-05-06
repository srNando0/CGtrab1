#pragma once

#include <vector>
//#include <memory>			<- collision, instance
//#include <optional>		<- collision, instance, shape

//#include <glm.hpp>		<- collision, hit, ray

//#include "instance.hpp"	<- collision
#include "collision.hpp"
#include "light.hpp"
//#include "ray.hpp"		<- collision, hit
//#include "hit.hpp"		<- collision



class Collision;
class Instance;
class Light;

class Scene {
public:
	std::vector<std::shared_ptr<Instance>> instances;
	std::vector<std::shared_ptr<Light>> lights;
	glm::vec4 ambientColor;
	glm::vec4 skyColor;
	
	Scene(glm::vec4 ambientColor, glm::vec4 skyColor);
	
	glm::vec4 traceRay(Ray ray, unsigned int recursion);
	std::optional<Collision> castRay(Ray ray);
	glm::vec4 getAmbient(Ray ray);
	glm::vec4 getSky(Ray ray);
};