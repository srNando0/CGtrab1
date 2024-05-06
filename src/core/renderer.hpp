#pragma once

//#include <memory>		<- scene, collision, instance

//#include <glm.hpp>	<- camera, ray

#include "film.hpp"
#include "camera.hpp"
#include "scene.hpp"



class Renderer {
private:
	const std::shared_ptr<Film> mFilm;
	const std::shared_ptr<Camera> mCamera;
	const std::shared_ptr<Scene> mScene;
	
	float linearToGamma(float x);
	glm::vec3 linearToGamma(glm::vec3 c);
	glm::vec4 linearToGamma(glm::vec4 c);
	
	glm::vec3 doTonemapping(glm::vec3 color, float r);
	glm::vec4 doTonemapping(glm::vec4 color, float r);
	
	glm::vec4 interpolateColor(glm::vec4 c1, glm::vec4 c2, float t);
public:
	Renderer(std::shared_ptr<Film> film, std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene);
	
	void render(const char* filename);
};