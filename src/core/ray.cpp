#include "ray.hpp"



/*
	Constructor and Destructor
*/
Ray::Ray(glm::vec3 origin, glm::vec3 dir) : origin(origin), dir(glm::normalize(dir)) {}

Ray::Ray(Ray ray, float t) : origin(ray.origin + t*ray.dir), dir(ray.dir) {}