#include "renderer.hpp"

#include <cstdlib>



/*
	Constructor and Destructor
*/
Renderer::Renderer(
	std::shared_ptr<Film> film,
	std::shared_ptr<Camera> camera,
	std::shared_ptr<Scene> scene
) : mFilm(film), mCamera(camera), mScene(scene) {}



/*
	Private Methods
*/
float Renderer::linearToGamma(float x) {
	return (x <= 0.0031308f) ? (12.92f*x) : (1.055f*glm::pow(glm::max(0.0f, x), 1.0f/2.4f) - 0.055f);
}

glm::vec3 Renderer::linearToGamma(glm::vec3 c) {
	return glm::vec3(
		linearToGamma(c.x),
		linearToGamma(c.y),
		linearToGamma(c.z)
	);
}

glm::vec4 Renderer::linearToGamma(glm::vec4 c) {
	return glm::vec4(
		linearToGamma(c.x),
		linearToGamma(c.y),
		linearToGamma(c.z),
		c.a
	);
}



glm::vec3 Renderer::doTonemapping(glm::vec3 color, float r) {
	// define ACES-CG
	glm::mat3 srgbToAp1(
		0.612494198536834, 0.070594251610915, 0.020727335004178,
		0.338737251923843, 0.917671483736251, 0.106882231793044,
		0.048855526064502, 0.011704306146428, 0.872338062223856
	);
	glm::mat3 ap1ToSrgb(
		1.707077341393391, -0.1310087341843325, -0.02450960122569158,
		-0.6199617703400125, 1.13899879428281, -0.1248238298364764,
		-0.08728719115306108, -0.007944958796604444, 1.149392018071762
	);
	
	glm::vec3 c = srgbToAp1*glm::vec3(color);
	glm::vec3 n = r*r*c*c;
	glm::vec3 u = glm::vec3(1.0f);
	glm::vec3 d = (r*c + u)*(r*c + u) + u;
	glm::vec3 t = ap1ToSrgb*(n/d);
	//glm::vec3 t = (n/d);
	
	return t;
}

glm::vec4 Renderer::doTonemapping(glm::vec4 color, float r) {
	return glm::vec4(
		doTonemapping(glm::vec3(color), 4.828427f),
		color.a
	);
}



glm::vec4 Renderer::interpolateColor(glm::vec4 c1, glm::vec4 c2, float t) {
	float _1ma = (1.0f - t)*(1.0f - c1.a) + t*(1.0f - c2.a);
	float a = 1.0f - _1ma;
	glm::vec3 ac = (1.0f - t)*c1.a*glm::vec3(c1) + t*c2.a*glm::vec3(c2);
	glm::vec3 c = a == 0.0f ? glm::vec3(0.0f) : ac/a;
	return glm::vec4(c, a);
}



/*
	Public Methods
*/
void Renderer::render(const char* filename) {
	for (float x = 0.0f; x < mFilm->resolution.x; x++) {
		for (float y = 0.0f; y < mFilm->resolution.y; y++) {
			// for each pixel, compute color
			glm::vec4 color(1.0f, 0.0f, 1.0f, 1.0f);
			
			for (unsigned int k = 0; k < mFilm->spp; k++) {
				// for each sample, compute a color inside pixel area at random
				float t = 1.0f/(k + 1.0f);
				
				// random subpixel position
				float epsilon1 = std::rand()/static_cast<float>(RAND_MAX);
				float epsilon2 = std::rand()/static_cast<float>(RAND_MAX);
				glm::vec2 epsilon = glm::vec2(epsilon1, epsilon2);
				
				// generating a ray
				glm::vec2 coord = glm::mat2(1.0f, 0.0f, 0.0f, -1.0f)*(
					2.0f*(glm::vec2(x, y) + epsilon)/mFilm->resolution - glm::vec2(1.0f)
				);
				Ray ray = mCamera->generateRay(coord);
				
				// mix color
				glm::vec4 newColor = doTonemapping(mScene->traceRay(ray, 0), 4.828427f);
				color = interpolateColor(color, newColor, t);
				//color = (1.0f - t)*color + t*newColor;
			}
			
			// save color
			unsigned int i = static_cast<unsigned int>(x);
			unsigned int j = static_cast<unsigned int>(y);
			mFilm->setColor(i, j, linearToGamma(color));
		}
	}
	
	// save image
	mFilm->saveImage(filename);
}