#pragma once

#include <glm.hpp>

#include "material.hpp"



class Hit {
public:
	const glm::vec4 origin;
	const glm::vec4 position;
	const glm::vec4 normal;
	const bool isBackfacing;
	const Material* const material;
	
	Hit(
		glm::vec4 origin,
		glm::vec4 position,
		glm::vec4 normal,
		bool isBackfacing,
		Material* material
	);
};