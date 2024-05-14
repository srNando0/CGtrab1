#include "material_functions.hpp"

#define PI (float) 3.141592653589793115997963468544185161590576171875



float material::phong(
	glm::vec3 light,
	glm::vec3 normal,
	glm::vec3 view,
	float shininess
) {
	glm::vec3 reflection = -glm::reflect(light, normal);
	
	float specular = glm::dot(reflection, view);
	//specular = glm::max(0.0f, specular);
	specular = glm::pow(specular, shininess);
	specular *= (shininess + 2.0f)/(2.0f*PI);
	
	return specular;
}



float material::beckmannD(float cosine, float alpha) {
	float a2 = alpha*alpha;
	float c2 = cosine*cosine;
	float k = (c2 - 1.0f)/(a2*c2);
	return glm::exp(k)/(PI*a2*c2*c2);
}

float material::ggxD(float cosine, float alpha) {
	float a2 = alpha*alpha;
	float c2 = cosine*cosine;
	float d = c2*(a2 - 1.0f) + 1.0f;
	return a2/(PI*d*d);
}



glm::vec3 material::fresnel(
	glm::vec3 color,
	float cosine
) {
	float x = 1.0f - cosine;
	float x5 = x*x*x*x*x;
	return color + (1.0f - color)*x5;
}



float material::cookTorrangG(
	glm::vec3 light,
	glm::vec3 normal,
	glm::vec3 view
) {
	glm::vec half = glm::normalize(light + view);
	float nh = glm::dot(normal, half);
	float nv = glm::dot(normal, view);
	float hv = glm::dot(half, view);
	float nl = glm::dot(normal, light);
	float hl = glm::dot(half, light);
	
	float g = 1.0f;
	g = glm::min(g, (2.0f*nh*nv)/hv);
	g = glm::min(g, (2.0f*nh*nl)/hl);
	return g;
}

float material::ggxG(
	glm::vec3 light,
	glm::vec3 normal,
	glm::vec3 view,
	float alpha
) {
	float a2 = alpha*alpha;
	float nl = glm::dot(normal, view);
	float nv = glm::dot(normal, view);
	
	float dl = nl + glm::sqrt(a2 + (1.0f - a2)*nl*nl);
	float dv = nv + glm::sqrt(a2 + (1.0f - a2)*nv*nv);
	return (4.0f*nl*nv)/(dl*dv);
}

float material::ggxV(
	glm::vec3 light,
	glm::vec3 normal,
	glm::vec3 view,
	float alpha
) {
	float a2 = alpha*alpha;
	float nl = glm::dot(normal, light);
	float nv = glm::dot(normal, view);
	
	float dl = nl + glm::sqrt(a2 + (1.0f - a2)*nl*nl);
	float dv = nv + glm::sqrt(a2 + (1.0f - a2)*nv*nv);
	return 1.0f/(dl*dv);
}



glm::vec3 material::cookTorranceGGX(
	glm::vec3 light,
	glm::vec3 normal,
	glm::vec3 view,
	glm::vec3 color,
	float alpha
) {
	glm::vec half = glm::normalize(light + view);
	float nh = glm::dot(normal, half);
	float hv = glm::dot(half, view);
	
	return glm::vec3(ggxD(nh, alpha));//(ggxD(nh, alpha)*ggxV(light, normal, view, alpha))*fresnel(color, hv);
}