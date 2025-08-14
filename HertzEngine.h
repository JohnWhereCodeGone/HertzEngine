#pragma once
#include "Camera.h"
#include "Meshmanager.h"
#include <iostream>


#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"


#include "MyDebug/Debugger.h"
//input



#define SCR_WIDTH 1920.0
#define SCR_HEIGHT 1080.0



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
	static Shader* DefaultShader;

	//returns Hertz deltatime.
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
	static Shader* GetDefaultShader();
	//input function holder
	Meshmanager* GetMeshMangr();
	


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void Shutdown();
	void Update();



private:
	Meshmanager* MeshManager;
	glm::mat4 projection;
	glm::mat4 view;


	GameState state;
	GLFWwindow* GameWindow;


	//todo -- fix function pointers for glCallbacks. think it's okay?	
protected:
	bool bShouldClose;
	static float fDeltaTime;
	float fPrevFrame = 0.0f;


};

