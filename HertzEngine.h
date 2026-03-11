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
//#include "Entity/EntityManager.h"
#include "TextureManager.h"


#define SCR_WIDTH 1920.0
#define SCR_HEIGHT 1080.0


class Meshmanager;
class HertzEditor;
class Lightmanager;
class PhysicsEngine2;
class EntityManager;

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
	std::shared_ptr<Meshmanager>	manager; //this is the manager actually used.
	std::shared_ptr<Camera>			cam;
	static std::shared_ptr<Shader>	DefaultShader;

	//returns Hertz::deltatime.
	static const double DeltaTime();
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

	std::shared_ptr<Camera>								GetCam() const;
	static std::shared_ptr<Shader>						GetDefaultShader();
	std::shared_ptr<Shader>								MakeDefaultShader();
	static std::vector<std::shared_ptr<HertzTexture>>	GetDefaultTexture(); //herlper
	std::shared_ptr<TextureManager>						GetTextureManager();
	std::shared_ptr<Lightmanager>						GetLightManager();
	//input function holder
	std::shared_ptr<Meshmanager>						GetMeshMangr(); // depricated
	


	static void						framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void							Shutdown();
	void							Update();
	void							MessageHandling(); //delete
	void							ProcessMessages(); //Spawns the worker thread - REAL FUNCTION
	void							WorkerThreadOBJ(); //delete
	std::shared_ptr<EntityManager>	GetEntityManager();
	std::shared_ptr<PhysicsEngine2> GetPhysicsEngine();
	std::shared_ptr<ShaderManager>	GetShaderManager();
	std::shared_ptr<HertzEditor>	GetEditor();

	bool bShouldClose;
	MessagingQueue messagequeue;
private:

	//UI
	std::shared_ptr<HertzEditor>	m_editor;

	Meshmanager*					MeshManager; //depricated

	std::shared_ptr<EntityManager>	m_EntityManager;
	std::shared_ptr<ShaderManager>	m_shaderManager;
	std::shared_ptr<TextureManager> m_textureManager;
	std::shared_ptr<Meshmanager>	m_meshman;
	std::shared_ptr<Lightmanager>	m_lightManager;
	std::shared_ptr<PhysicsEngine2> m_PhysicsEngine;
	
	glm::mat4						projection;
	glm::mat4						view;

	GameState						state;
	GLFWwindow*						GameWindow;

	bool							m_bIsSimulating;

	//Graduation project

	double							m_SimulationTimeStep;
	double							m_SimulationAccumulator;


	//todo -- fix function pointers for glCallbacks. think it's okay?	
protected: //this is useless
	static double fDeltaTime;
	double fPrevFrame = 0.0f;


};

