
#include "hertzinputs.h"
#include "../HertzEngine.h"

//GLFW
#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



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

	/*
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
	}
	*/

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

void HertzInput::imouse_callback(GLFWwindow* window)
{
	HertzEngine *eng = reinterpret_cast<HertzEngine*>(glfwGetWindowUserPointer(window));
	//find way to make interpret not necessary.
	

	//MyWindowHandler* handler = reinterpret_cast<MyWindowHandler*>(glfwGetWindowUserPointer(window));
	
	double xposin, yposin;
	glfwGetCursorPos(window, &xposin, &yposin);


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
	//this is really cursed. and doesn't work for anything except imgui -- find a fucking fix.

	ImGuiIO& io = ImGui::GetIO();

	xOffset = io.MouseWheel;
	yOffset = io.MouseWheelH;

	HertzEngine* eng = reinterpret_cast<HertzEngine*>(glfwGetWindowUserPointer(window));
	//std::cout << eng->GetCam()->fCamSpeed << std::endl;
	float delta = static_cast<float>(yOffset);
	eng->GetCam()->CameraScroll(delta);

	//std::cout << yOffset << std::endl;
}

void HertzInput::iKeyCallbackImproved(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	HertzEngine* eng = reinterpret_cast<HertzEngine*>(glfwGetWindowUserPointer(window));
	float deltaTime = HertzEngine::DeltaTime();

	ImGuiIO& io = ImGui::GetIO();

	if (action == GLFW_PRESS)
	{
		/*
		if (key == GLFW_KEY_9)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
			
		}
		if (key == GLFW_KEY_8)
		{
			glfwFocusWindow(window);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			int i = glfwGetInputMode(window, GLFW_CURSOR);
			if (i == GLFW_CURSOR_DISABLED)
			{
				//std::cout << "it's capturin" << std::endl;
			}
			
			io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}
		*/
		if (key == GLFW_KEY_ESCAPE)
		{
			eng->Shutdown();
		}
		if (key == GLFW_KEY_F1)
		{
			bool check = eng->GetCam()->m_takesInput;
			//TODO: Create an actual input/game state
			if (check)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
				eng->GetCam()->m_takesInput = false;
			}
			else
			{

				glfwFocusWindow(window);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				int i = glfwGetInputMode(window, GLFW_CURSOR);
				if (i == GLFW_CURSOR_DISABLED)
				{
					//std::cout << "it's capturin" << std::endl;
				}

				io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
				eng->GetCam()->m_takesInput = true;
			}
		}


	}

	/*
	if (action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_W)
		{
			eng->GetCam()->CameraInput(FORWARD, deltaTime);
		}
		if (key == GLFW_KEY_SPACE)
		{
			eng->GetCam()->CameraInput(UP, deltaTime);
		}
		if (key == GLFW_KEY_LEFT_CONTROL)
		{
			eng->GetCam()->CameraInput(DOWN, deltaTime);
		}
		if (key == GLFW_KEY_A)
		{
			eng->GetCam()->CameraInput(LEFT, deltaTime);
		}
		if (key == GLFW_KEY_S)
		{
			eng->GetCam()->CameraInput(BACK, deltaTime);
		}
		if (key == GLFW_KEY_D)
		{
			eng->GetCam()->CameraInput(RIGHT, deltaTime);
		}
	}
	*/


}





