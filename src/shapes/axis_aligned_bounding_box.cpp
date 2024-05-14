#include "axis_aligned_bounding_box.hpp"



/*
	Constructor and Destructor
*/
AxisAlignedBoundingBox::AxisAlignedBoundingBox(
	glm::vec3 position,
	glm::vec3 dimensions
) : Shape(position), dimensions(dimensions) {}



/*
	Public Methods
*/
std::optional<Hit> AxisAlignedBoundingBox::castRayHook(Ray ray) {
	
}