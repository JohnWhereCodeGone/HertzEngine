#pragma once
#include <iostream>

//ui


#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "Camera.h"

#include "Shaders/HertzShader.h"
#include <filesystem>
#include "Texture/HertzTexture.h"

#include "Camera.h"

//objects
#include "Mesh.h"
#include "ObjLoader.h"
#include "Meshmanager.h"
#include "HertzEngine.h"
#include "Objects/VirtualObject.h"



std::string crate = ".\\Dependencies\\Crate.obj";
std::string monky = ".\\Dependencies\\monkey.obj";



// mutex
// collis, wireframe - 
//  DO MUTEX - PHYSICS



// producer/consumer - application




// have the main thread check its own list for pushed data from other threads.


int main()
{
	HertzEngine engine;
	GLFWwindow* win = engine.GetWindow();
	

	engine.GetMeshMangr()->AddMesh(crate.c_str(), HertzEngine::DefaultShader);
	engine.GetMeshMangr()->AddMesh(monky.c_str(), HertzEngine::DefaultShader);
	
	VirtualObject obj;
	VirtualObject obj2;

	while (!glfwWindowShouldClose(win))
	{
		

		engine.Update();
	}
}



