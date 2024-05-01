#pragma once

#include <glm.hpp>

#include "hit.hpp"



class Hit;

class Material {
public:
	virtual ~Material();
	virtual glm::vec4 evaluate(Hit hit, unsigned int recursion) = 0;
};