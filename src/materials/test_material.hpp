#pragma once

//#include <glm.hpp>

#include "../core/material.hpp"



class TestMaterial : public Material {
public:
	glm::vec4 computeColor(Hit hit, Scene& scene, unsigned int recursion);
};