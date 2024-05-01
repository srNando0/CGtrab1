#pragma once

#include <glm.hpp>

#include "hit.hpp"



class Material {
public:
	virtual glm::vec4 evaluate(Hit hit, unsigned int recursion) = 0;
};