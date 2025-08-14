
#include "hertzinputs.h"
#include "../HertzEngine.h"

//GLFW
#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"




InputData HertzInput::indata = {};

/*
HertzInput::HertzInput()
{
	indata.bFirstMouse = true;
	indata.fCameraSpeed = 2.5f;
	indata.flastX = 810;
	indata.flastY = 540;
}
*/

void HertzInput::iprocessInput(GLFWwindow* window)
{
	HertzEngine* eng = reinterpret_cast<HertzEngine*>(glfwGetWindowUserPointer(window));
	float deltaTime = HertzEngine::DeltaTime();


	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		eng->Shutdown();
	}

	if (glfwGetKey(eng->GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		float apple4 = 0.f;
		std::cout << apple4 << std::endl;
		if (apple4 <= 1.f)
			apple4 += 0.001f;
	}

	if (glfwGetKey(eng->GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		float apple4 = 0.f;
		std::cout << apple4 << std::endl;
		if (apple4 >= 0)
			apple4 -= 0.001f;

	}

	//Camera

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //improve this.
	{
		eng->GetCam()->CameraInput(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		eng->GetCam()->CameraInput(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		eng->GetCam()->CameraInput(DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		eng->GetCam()->CameraInput(BACK, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		eng->GetCam()->CameraInput(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		eng->GetCam()->CameraInput(RIGHT, deltaTime);
	}
}

void HertzInput::imouse_callback(GLFWwindow* window, double xposin, double yposin)
{
	HertzEngine *eng = reinterpret_cast<HertzEngine*>(glfwGetWindowUserPointer(window));
	//find way to make interpret not necessary.
	

	//MyWindowHandler* handler = reinterpret_cast<MyWindowHandler*>(glfwGetWindowUserPointer(window));
	

	float xpos = static_cast<float>(xposin);
	float ypos = static_cast<float>(yposin);

	

	if (indata.bFirstMouse)
	{


		indata.flastX = xpos;
		indata.flastY = ypos;
		indata.bFirstMouse = false;
	}


	float xOffset = xpos - indata.flastX;
	float yOffset = indata.flastY - ypos;

	indata.flastX = xpos;
	indata.flastY = ypos;

	
	eng->GetCam()->MouseMovement(xOffset, yOffset);
}

void HertzInput::imouse_scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	HertzEngine* eng = reinterpret_cast<HertzEngine*>(glfwGetWindowUserPointer(window));
	std::cout << eng->GetCam()->fCamSpeed << std::endl;
	float delta = static_cast<float>(yOffset);
	eng->GetCam()->CameraScroll(delta);
	std::cout << yOffset << std::endl;
}





