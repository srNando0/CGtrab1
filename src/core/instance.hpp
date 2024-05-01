#pragma once

#include "shape.hpp"
#include "material.hpp"



class Instance {
private:
	Shape mShape;
	Material* mMaterial;

public:
	Instance(Shape shape, Material* material);
	~Instance();
};