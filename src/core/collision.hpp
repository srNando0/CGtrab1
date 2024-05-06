#pragma once

//#include <memory>		<- instance

#include "hit.hpp"
#include "instance.hpp"



class Instance;

class Collision {
public:
	const Hit hit;
	const std::shared_ptr<Instance> instance;
	
	Collision(Hit hit, std::shared_ptr<Instance> instance);
};