#pragma once

#include <memory>

#include "shape.hpp"
#include "material.hpp"



class Material;

class Instance {
public:
	std::shared_ptr<Shape> shape;
	std::shared_ptr<Material> material;
	
	Instance(
		std::shared_ptr<Shape> shape,
		std::shared_ptr<Material> material
	);
};