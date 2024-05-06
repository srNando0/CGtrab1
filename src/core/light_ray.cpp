#include "light_ray.hpp"



/*
	Constructor and Destructor
*/
LightRay::LightRay(glm::vec3 color, glm::vec3 dir) : color(color), dir(glm::normalize(dir)) {};