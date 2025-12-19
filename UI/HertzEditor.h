#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Threading/MessagingQueue.h"


class EntityManager;
class Camera;
class ShaderManager;
class Meshmanager;
class TextureManager;
class Lightmanager;
class PhysicsEngine2;

class HertzEditor
{
public:
	HertzEditor(std::shared_ptr<Camera> cam, std::shared_ptr<EntityManager> man, std::shared_ptr<TextureManager> texman, std::shared_ptr <ShaderManager> shadman, std::shared_ptr<Meshmanager> meshman, std::shared_ptr<Lightmanager> lightman, std::shared_ptr<PhysicsEngine2> physen) : m_EntityManager(man), m_camRef(cam), m_TextureManager(texman), m_ShaderManager(shadman), m_MeshManager(meshman), m_charBuffer(), m_lightManager(lightman), m_physicsEngine(physen) {};

	void EditorUI(GLFWwindow* window);
	void InitUI(std::shared_ptr<Camera> cam);

private:

	char* m_charBuffer[256];
	std::string				m_stringBuffer;


	std::shared_ptr<Camera> m_camRef;

	std::shared_ptr<EntityManager>	m_EntityManager;
	std::shared_ptr<TextureManager> m_TextureManager;
	std::shared_ptr<ShaderManager>	m_ShaderManager;
	std::shared_ptr<Meshmanager>	m_MeshManager;
	std::shared_ptr<Mesh>			m_selectedMesh;
	std::shared_ptr<Lightmanager>	m_lightManager;
	
	
	std::shared_ptr<PhysicsEngine2> m_physicsEngine;



	//Selectables.

	bool m_bIsSelected;
	int m_selectedIndex;
	double days = 0.0;
};

