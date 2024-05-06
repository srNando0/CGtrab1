#include "camera.hpp"

#include <cmath>

#define PI 3.141592653589793115997963468544185161590576171875



/*
	Constructor and Destructor
*/
Camera::Camera(
	glm::vec3 center,
	glm::vec3 eye,
	glm::vec3 up,
	float ratio,
	float fieldOfView
) : mCenter(center), mEye(eye), mUp(up), mRatio(ratio),
mTangent(tanf((PI/360.0f)*fieldOfView)), viewMatrix(lookAt(center, eye, up)) {}



/*
	Private Methods
*/
glm::mat4 Camera::lookAt(glm::vec3 center, glm::vec3 eye, glm::vec3 up) {
	glm::vec3 z = glm::normalize(eye - center);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::normalize(glm::cross(z, x));
	
	return glm::mat4(
		glm::vec4(x, -glm::dot(x, eye)),
		glm::vec4(y, -glm::dot(y, eye)),
		glm::vec4(z, -glm::dot(z, eye)),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}



/*
	Public Methods
*/
Ray Camera::generateRay(glm::vec2 coord) {
	glm::vec2 pixel = glm::vec2(mRatio*coord.x, coord.y);
	glm::vec4 homoCoord = glm::vec4(mTangent*pixel, -1.0f, 0.0f);
	glm::vec3 dir = glm::vec3(viewMatrix*homoCoord);
	return Ray(mEye, dir);
}