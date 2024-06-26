#include <iostream>
//#include <memory>			<- scene, collision, instance

#include <chrono>
#include <iomanip>

//#include <glm.hpp>		<- camera, ray

#include "core/renderer.hpp"
#include "core/film.hpp"
#include "core/camera.hpp"
#include "core/scene.hpp"
//#include "core/instance.hpp"	<- scene, collision
//#include "core/light.hpp"		<- scene
//#include "core/material.hpp"	<- scene, collision, instance

#include "shapes/sphere.hpp"
#include "shapes/infinite_plane.hpp"

#include "materials/phong_material.hpp"
#include "materials/smooth_material.hpp"
#include "materials/transparent_material.hpp"
//#include "materials/cook_torrance_material.hpp"
//#include "materials/test_material.hpp"

#include "lights/point_light.hpp"



/*
	Test
*/



int main() {
	// time
	auto start = std::chrono::high_resolution_clock::now();
	
	// essentials
	std::shared_ptr<Film> film = std::make_shared<Film>(
		//glm::vec2(1920.0f, 1080.0f),
		glm::vec2(640.0f, 480.0f),
		1
	);
	
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(
		glm::vec3(3.0f, 10.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		//16.0f/9.0f,
		4.0f/3.0f,
		75
	);
	
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(
		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		3
	);
	
	
	
	// instances
	std::shared_ptr<Instance> sphere = std::make_shared<Instance>(
		std::make_shared<Sphere>(
			glm::vec3(0.0f, 8.0f, 2.4f),
			2.0f
		),
		std::make_shared<TransparentMaterial>(
			2.0f*glm::vec3(1.0f, 0.8f, 0.0f),
			0.9f
		)
		/*std::make_shared<SmoothMaterial>(
			glm::vec3(1.0f, 0.0f, 0.0f),
			0.0f,
			0.5f
		)*/
		/*std::make_shared<PhongMaterial>(
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			0.5f,
			40.0f
		)*/
	);
	sphere->shape->matrix = glm::mat3(
		1.0f, 0.0f, 0.3f,
		0.0f, 0.2f, 0.0f,
		0.3f, 0.0f, 1.0f
	);
	
	std::shared_ptr<Instance> floor = std::make_shared<Instance>(
		std::make_shared<InfinitePlane>(
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		),
		std::make_shared<SmoothMaterial>(
			glm::vec3(1.0f, 1.0f, 1.0f),
			0.0f,
			0.0f
		)/*
		std::make_shared<PhongMaterial>(
			glm::vec3(1.0f, 1.0f, 1.0f),
			0.0f,
			400.0f
		)*/
	);
	
	scene->instances.push_back(sphere);
	scene->instances.push_back(floor);
	
	
	
	// lights
	std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(
		20.0f*glm::vec3(1.0f, 1.0f, 1.0f),
		std::make_shared<Sphere>(glm::vec3(3.5f, 4.0f, 4.5f), 0.2f),
		*scene
	);
	
	std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(
		40.0f*glm::vec3(1.0f, 1.0f, 1.0f),
		std::make_shared<Sphere>(glm::vec3(0.0f, 40.0f, 6.0f), 0.2f),
		*scene
	);
	
	scene->lights.push_back(pointLight1);
	scene->lights.push_back(pointLight2);
	
	
	
	// rendering
	Renderer renderer(film, camera, scene);
	renderer.render("ray_tracing.png");
	
	
	
	// test
	auto end = std::chrono::high_resolution_clock::now();
	double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	
	std::cout << "Yes!\nTime: " <<
		std::fixed << time_taken << std::setprecision(9)
		<< " seconds." << std::endl;
	
	return 0;
}