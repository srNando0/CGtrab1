#include "instance.hpp"



/*
	Constructor and Destructor
*/
Instance::Instance(Shape shape, Material* material) : mShape(shape), mMaterial(material) {}

Instance::~Instance() {
	delete mMaterial;
}