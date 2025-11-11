#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Threading/MessagingQueue.h"


class EntityManager;
class Camera;

class HertzEditor
{
public:
	HertzEditor(std::shared_ptr<Camera> cam, std::shared_ptr<EntityManager> man) : m_EntityManager(man), m_camRef(cam)  {};

	void EditorUI(GLFWwindow* window);
	void InitUI(std::shared_ptr<Camera> cam);

private:


	std::shared_ptr<Camera> m_camRef;
	std::shared_ptr<EntityManager> m_EntityManager;
};

