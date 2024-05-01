#include "hit.hpp"



/*
	Constructor and Destructor
*/
Hit::Hit(
	glm::vec4 origin,
	glm::vec4 position,
	glm::vec4 normal,
	bool isBackfacing,
	Material* material
) : origin(origin), position(position), normal(normal), isBackfacing(isBackfacing), material(material) {}