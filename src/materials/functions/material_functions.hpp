#include <glm.hpp>

#define PI 3.141592653589793115997963468544185161590576171875



/*
	integral(
		integral(
			f(w_i, theta, phi)*sin(2*theta)/2,
			theta,
			0,
			pi/2
		),
		phi,
		0,
		2*pi
	) <= 1
*/



namespace material {
	glm::vec3 phong(
		glm::vec3 view,
		glm::vec3 normal,
		glm::vec3 light,
		glm::vec3 color,
		float shininess
	) {
		glm::vec3 reflection = -glm::reflect(light, normal);
		
		float specular =glm::dot(reflection, view);
		specular = fmaxf(0.0f, specular);
		specular = powf(specular, shininess);
		specular *= (shininess + 1.0f)/(2.0f*PI);
		
		
		return specular*color;
	}
	
	
	
	glm::vec3 phong(
		glm::vec3 view,
		glm::vec3 normal,
		glm::vec3 light,
		glm::vec3 color,
		float shininess
	) {
		glm::vec3 reflection = -glm::reflect(light, normal);
		
		float specular =glm::dot(reflection, view);
		specular = fmaxf(0.0f, specular);
		specular = powf(specular, shininess);
		specular *= (shininess + 1.0f)/(2.0f*PI);
		
		
		return specular*color;
	}
	
	
	
	glm::vec3 cookTorrance(
		glm::vec3 view,
		glm::vec3 normal,
		glm::vec3 light,
		glm::vec3 dColor,
		glm::vec3 sColor,
		float shininess
	) {
		glm::vec3 reflection = -glm::reflect(light, normal);
		
		float diffusion = glm::dot(light, normal);
		diffusion = fmaxf(0.0f, diffusion);
		
		float specular =glm::dot(reflection, view);
		specular = fmaxf(0.0f, specular);
		specular = powf(specular, shininess);
		specular *= (shininess + 1.0f)/(2.0f*PI);
		
		
		return diffusion*dColor + specular*sColor;
	}
}