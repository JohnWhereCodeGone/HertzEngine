#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../Camera.h"
#include "../Threading/MessagingQueue.h"



class HertzEditor
{
public:
	HertzEditor();

	void EditorUI(GLFWwindow* window);
	void InitUI(std::shared_ptr<Camera> cam);

private:


	std::shared_ptr<Camera> camRef;
	
};

