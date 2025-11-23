#pragma once
#include <iostream>

//ui


#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include <thread>

#include "Shaders/HertzShader.h"
#include <filesystem>
#include "Texture/HertzTexture.h"

#include "Camera.h"

//objects
#include "Mesh.h"
#include "ObjLoader.h"
#include "../Mesh/Meshmanager.h"
#include "HertzEngine.h"
#include "Objects/VirtualObject.h"
#include "Entity/Entity.h"
#include "Serializer/Serializer.h"

#include "../Lights/Lightmanager.h"

std::string crate = ".\\Dependencies\\Crate.obj";
std::string monky = ".\\Dependencies\\monkey.obj";



// mutex
// collis, wireframe - 
//  DO MUTEX - PHYSICS



// producer/consumer - application




// have the main thread check its own list for pushed data from other threads.


int main()
{
	using EntityPtr = std::shared_ptr<Entity>;
	HertzEngine engine;
	GLFWwindow* win = engine.GetWindow();

	std::shared_ptr<Lightmanager> lightman = engine.GetLightManager();
	
	
	lightman->CreateLight(Pointlighter);
	lightman->CreateLight(Spotlighter);
	lightman->CreateLight(DiffuseLighter);
	
	auto EntityManager = engine.GetEntityManager();
	std::shared_ptr<Entity> test = EntityManager->CreateEntity();

	/*
	std::shared_ptr<Entity> test1 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test12 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test3 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test34 = EntityManager->CreateEntity();
	*/

	std::shared_ptr<ObjMessage> msgtest = std::make_shared<ObjMessage>(crate);
	//engine.messagequeue.Push(msgtest);

	std::shared_ptr<ObjMessage> msgMonkey = std::make_shared<ObjMessage>(monky);
	engine.GetTextureManager()->LoadTexture(".\\Texture\\th.jpg", Diffuse);

	//engine.messagequeue.Push(msgMonkey);

	

	std::shared_ptr<Mesh> meshref = engine.manager->GetMesh(crate.c_str());

	
	test->GetTransform()->AddVelocity(glm::vec3(4.0f, 0.f, 0.f));


	//engine.GetMeshMangr()->AddMesh(crate.c_str(), HertzEngine::DefaultShader);
	//engine.GetMeshMangr()->AddMesh(monky.c_str(), HertzEngine::DefaultShader);
	

	float time = 0;


	engine.GetMeshMangr()->LoadDataMesh();

	while (!engine.bShouldClose)
	{
		//std::cout << engine.bShouldClose << std::endl;
		engine.Update();

		time += HertzEngine::DeltaTime();

		/*
		if (time >= 2.0f && test->GetMesh() == nullptr)
		{
			test->SetMesh(engine.manager->GetMesh(crate.c_str()));

			
		}
		*/
	}
	engine.GetMeshMangr()->SaveDataMesh(nullptr);
}



