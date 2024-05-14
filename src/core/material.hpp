#pragma once

//#include <glm.hpp>	<- scene, collision, hit, ray

//#include "hit.hpp"	<- scene, collision
#include "scene.hpp"



class Scene;

class Material {
public:
	const bool mIsTransparent;
	
	Material(bool isTransparent);
	virtual ~Material();
	
	virtual glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion) = 0;
};