#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Threading/MessagingQueue.h"

class HertzEditor
{
public:
	static void EditorUI(GLFWwindow* window);
	void InitUI(MessagingQueue &queue);

private:

	MessagingQueue &m_messagequeue;
	
};

