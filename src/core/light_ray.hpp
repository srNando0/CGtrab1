#pragma once

#include <glm.hpp>



class LightRay {
public:
	const glm::vec3 color;
	const glm::vec3 dir;
	
	LightRay(glm::vec3 color, glm::vec3 dir);
};