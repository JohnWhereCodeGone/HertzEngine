#pragma once
#include "Camera.h"
#include <iostream>


#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Threading/MessagingQueue.h"

#include "MyDebug/Debugger.h"
//input

#include "Shaders/ShaderManager.h"
#include "Entity/EntityManager.h"
#include "TextureManager.h"


#define SCR_WIDTH 1920.0
#define SCR_HEIGHT 1080.0


class Meshmanager;

enum GameState
{
	RUNNING,
	PAUSED,
};

class HertzEngine
{
public:

public:
	HertzEngine();
	GLFWwindow* GameInit();


	//defaults & managers;
	Meshmanager* manager;
	Camera* cam;
	static std::shared_ptr<Shader> DefaultShader;

	//returns Hertz::deltatime.
	static const float DeltaTime();
	GLFWwindow* GetWindow() //must be inline or there'll be a linker error.
	{
		if (GameWindow)
		{
			return GameWindow;

		}
		else
		{
			std::cerr << "Fatal error! GameWindow is null" << std::endl;
			__debugbreak;
			return nullptr;
		}
	};

	Camera* GetCam();
	static std::shared_ptr<Shader> GetDefaultShader();
	std::shared_ptr<Shader> MakeDefaultShader();
	static std::vector<std::shared_ptr<HertzTexture>> GetDefaultTexture(); //herlper
	//input function holder
	Meshmanager* GetMeshMangr();
	


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void Shutdown();
	void Update();
	void MessageHandling(); //delete
	void ProcessMessages(); //Spawns the worker thread - REAL FUNCTION
	void WorkerThreadOBJ(); //delete
	std::shared_ptr<EntityManager> GetEntityManager();


	bool bShouldClose;
	MessagingQueue messagequeue;
private:
	Meshmanager* MeshManager;
	std::shared_ptr<EntityManager> m_EntityManager;
	std::shared_ptr<ShaderManager> m_shaderManager;
	glm::mat4 projection;
	glm::mat4 view;
	TextureManager man;

	GameState state;
	GLFWwindow* GameWindow;


	//todo -- fix function pointers for glCallbacks. think it's okay?	
protected:
	static float fDeltaTime;
	float fPrevFrame = 0.0f;


};

