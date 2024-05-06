#include "instance.hpp"



/*
	Constructor and Destructor
*/
Instance::Instance(
	std::shared_ptr<Shape> shape,
	std::shared_ptr<Material> material
) : shape(shape), material(material) {}