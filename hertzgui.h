#pragma once
#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"


class HertzGui
{

public:
	void GuiInit(GLFWwindow* myWindow);
	void startRenderLoop();
	void endRenderLoop();
	~HertzGui();


};

