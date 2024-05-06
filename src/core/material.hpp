#pragma once

//#include <glm.hpp>	<- scene, collision, hit, ray

//#include "hit.hpp"	<- scene, collision
#include "scene.hpp"



class Scene;

class Material {
public:
	virtual ~Material();
	virtual glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion) = 0;
};