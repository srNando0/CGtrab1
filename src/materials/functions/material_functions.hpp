#pragma once

#include <glm.hpp>



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
	float phong(
		glm::vec3 light,
		glm::vec3 normal,
		glm::vec3 view,
		float shininess
	);

	float beckmannD(float cosine, float alpha);
	float ggxD(float cosine, float alpha);
	
	glm::vec3 fresnel(
		glm::vec3 color,
		float cosine
	);
	
	float cookTorrangG(
		glm::vec3 light,
		glm::vec3 normal,
		glm::vec3 view
	);
	float ggxG(
		glm::vec3 light,
		glm::vec3 normal,
		glm::vec3 view,
		float alpha
	);
	float ggxV(
		glm::vec3 light,
		glm::vec3 normal,
		glm::vec3 view,
		float alpha
	);
	
	glm::vec3 cookTorranceGGX(
		glm::vec3 light,
		glm::vec3 normal,
		glm::vec3 view,
		glm::vec3 color,
		float alpha
	);
}