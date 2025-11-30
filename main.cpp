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
#include "../Physics/Physics2/CubeCollider.h"
#include "Physics/Physics2/PhysicsEngine2.h"

std::string crate = ".\\Dependencies\\Crate.obj";
std::string monky = ".\\Dependencies\\monkey.obj";
std::string sphere = ".\\Mesh\\sphere2.obj";




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
	std::shared_ptr<PhysicsEngine2> physics = engine.GetPhysicsEngine();

	std::shared_ptr<Lightmanager> lightman = engine.GetLightManager();
	
	
	lightman->CreateLight(Pointlighter);
	lightman->CreateLight(Spotlighter);
	lightman->CreateLight(DiffuseLighter);
	
	auto EntityManager = engine.GetEntityManager();

	std::shared_ptr<Entity> test = EntityManager->CreateEntity();
	test->SetCollider(physics->CreateCollider(Sphere, test));

	std::shared_ptr<Entity> test2 = EntityManager->CreateEntity();
	test2->SetCollider(physics->CreateCollider(Cube, test2));
	test2->GetTransform()->SetPos(glm::vec3(0.0f, -1.f, 0.0f));

	std::shared_ptr<Entity> ground = EntityManager->CreateEntity();
	ground->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 100.f));
	ground->GetTransform()->SetPos(glm::vec3(0.0f, -10.f, 0.0f));

	std::shared_ptr<CubeCollider> groundcollider = std::static_pointer_cast<CubeCollider>(physics->CreateCollider(Cube, ground));
	groundcollider->m_bHasGravity = false;
	groundcollider->m_isKinematic = true;
	ground->SetCollider(groundcollider);

	

	/*
	std::shared_ptr<Entity> test1 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test12 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test3 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test34 = EntityManager->CreateEntity();
	*/

	std::shared_ptr<ObjMessage> msgtest = std::make_shared<ObjMessage>(sphere);
	//engine.messagequeue.Push(msgtest);

	std::shared_ptr<ObjMessage> msgMonkey = std::make_shared<ObjMessage>(monky);
	engine.GetTextureManager()->LoadTexture(".\\Texture\\th.jpg", Diffuse);

	//engine.messagequeue.Push(msgMonkey);

	

	std::shared_ptr<Mesh> meshref = engine.manager->GetMesh(crate.c_str());

	
	test->GetTransform()->AddVelocity(glm::vec3(4.0f, 0.f, 0.f));


	//engine.GetMeshMangr()->AddMesh(crate.c_str(), HertzEngine::DefaultShader);
	//engine.GetMeshMangr()->AddMesh(monky.c_str(), HertzEngine::DefaultShader);
	

	float time = 0;

	std::shared_ptr<Camera> camref = engine.GetCam();

	engine.GetMeshMangr()->LoadDataMesh();

	while (!engine.bShouldClose)
	{
		//std::cout << engine.bShouldClose << std::endl;
		engine.Update();

		time += HertzEngine::DeltaTime();

		//physics->RayCast(camref->vPos, camref->vFront);

		/*
		if (time >= 2.0f && test->GetMesh() == nullptr)
		{
			test->SetMesh(engine.manager->GetMesh(crate.c_str()));

			
		}
		*/
	}
	engine.GetMeshMangr()->SaveDataMesh(nullptr);
}



