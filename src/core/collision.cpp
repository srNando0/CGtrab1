#include "collision.hpp"



/*
	Constructor and Destructor
*/
Collision::Collision(Hit hit, std::shared_ptr<Instance> instance) : hit(hit), instance(instance) {}