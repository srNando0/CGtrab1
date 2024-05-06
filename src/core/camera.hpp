#pragma once

//#include <glm.hpp>	<- ray

#include "ray.hpp"



class Camera {
private:
	glm::vec3 mCenter;
	glm::vec3 mEye;
	glm::vec3 mUp;
	float mRatio;
	
	float mTangent;
	glm::mat4 viewMatrix;
	
	glm::mat4 lookAt(glm::vec3 center, glm::vec3 eye, glm::vec3 up);

public:
	Camera(
		glm::vec3 center,
		glm::vec3 eye,
		glm::vec3 up,
		float ratio,
		float fieldOfView
	);
	Ray generateRay(glm::vec2 coord);
};