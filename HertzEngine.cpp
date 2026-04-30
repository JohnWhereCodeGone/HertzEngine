#include "HertzEngine.h"
#include "input/hertzinputs.h" 
#include "../UI/HertzEditor.h"
#include <thread>
#include "../Threading/MipMapMessage.h"
#include "../Mesh/Meshmanager.h"
#include "../Lights/Lightmanager.h"
#include "Physics/Physics2/PhysicsEngine2.h"
#include "../Mesh/Trail.h"
#include "../Entity/Entity.h"
#include "../Entity/EntityManager.h"


std::shared_ptr<Shader> HertzEngine::DefaultShader = nullptr;
std::unique_ptr<Trail> trailTest;
std::shared_ptr<Entity> entityTest;


double HertzEngine::fDeltaTime = 0.0f;

void HertzEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	HertzEngine* instance = static_cast<HertzEngine*>(glfwGetWindowUserPointer(window));

	glViewport(0, 0, width, height);
	instance->projection = glm::perspective(glm::radians(instance->GetCam()->fZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
}

void HertzEngine::Shutdown()
{
	this->bShouldClose = true;
	glfwSetWindowShouldClose(GameWindow, bShouldClose);
}

HertzEngine::HertzEngine()
{
	bShouldClose = false;
	state = GameState::RUNNING;
	manager = std::make_shared<Meshmanager>();

	m_lightManager = std::make_shared<Lightmanager>();
	m_EntityManager = std::make_shared<EntityManager>();
	
	//simulation
	m_SimulationTimeStep = 100;
	m_SimulationAccumulator = 0;


	//Cam Setup
	cam = std::make_shared<Camera>(std::static_pointer_cast<Spotlight>(m_lightManager->CreateLight(Spotlighter)));
	projection = glm::perspective(glm::radians(cam->fZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);  //depricated, see camera class
	fDeltaTime = 0.0f;
	m_PhysicsEngine = std::make_shared<PhysicsEngine2>(*this);// this is terrible
	m_editor = std::make_shared<HertzEditor>(this->cam, m_EntityManager, m_textureManager, m_shaderManager, manager, m_lightManager, m_PhysicsEngine);

	// Shader Setup:

	
	m_bIsSimulating = false;

	GameWindow = GameInit();
	DefaultShader = ShaderManager::MakeShader();
	DefaultShader->setFloat("material.shine", 264.f);


	
	
	//DELETE ME
	/*
	entityTest = m_EntityManager->CreateEntity();
	entityTest->GetTransform()->SetPos(glm::dvec3(0));


	

	trailTest = std::make_unique<Trail>(entityTest->GetTransform());
	*/

	//initialize view
	
}

GLFWwindow* HertzEngine::GameInit()
{
	// Window Setup
	if (!glfwInit())
	{
		std::cout << "Fatal Error, GLFW failed init" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //used to give the GUI system some ideas of how this window wants to be treated. shuts down if opengl v3 ain't on pc.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
#endif

	GameWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GAB GAY", NULL, NULL);

	if (!GameWindow)
	{
		std::cout << "window creation failed." << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(GameWindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return nullptr;
	}//getproc = current function pointers for OS.
	//gladLoadGL();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetWindowUserPointer(GameWindow, this);

	glfwSetFramebufferSizeCallback(GameWindow, framebuffer_size_callback);
	//glfwSetScrollCallback(GameWindow, HertzInput::imouse_scroll_callback);
	//glfwSetCursorPosCallback(GameWindow, HertzInput::imouse_callback);

	glfwSetInputMode(GameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(GameWindow, HertzInput::iKeyCallbackImproved);
	glfwSetWindowOpacity(GameWindow, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// UI init;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	ImFontConfig conf;


	conf.OversampleH = 3.f;
	conf.OversampleV = 1.f;
	conf.RasterizerMultiply = 1.5f;
	conf.GlyphExtraSpacing.x = 1.0f;

	io.Fonts->AddFontFromFileTTF(".\\Resources\\Fonts\\Montserrat-Italic-VariableFont_wght.ttf", 18.f, &conf);


	ImGui_ImplGlfw_InitForOpenGL(GameWindow, true);
	ImGui_ImplOpenGL3_Init();


	//threading



	// Default Shader.

	return GameWindow;
}

const double HertzEngine::DeltaTime()
{
	return fDeltaTime;
}



std::shared_ptr<Camera> HertzEngine::GetCam() const
{
	if (cam)
		return cam;
	else
		std::cerr << "[HertzEngine] Camera was nullptr" << std::endl;
	return nullptr;
		
}

std::shared_ptr<Shader> HertzEngine::GetDefaultShader()
{
	
	std::shared_ptr<Shader> ShaderInstance = ShaderManager::MakeShader(nullptr);
	if (!ShaderInstance)
	{
		return nullptr;
	}
	ShaderInstance->setFloat("material.shine", 264.f);
	DefaultShader = ShaderInstance;
	ShaderInstance->debugName = std::to_string(reinterpret_cast<uintptr_t>(ShaderInstance.get()));
	return ShaderInstance;
	/*
	if (DefaultShader)
	{
		return DefaultShader;

	}
	else
	{
		std::cerr << "Default shader was nullptr" << std::endl;
		return nullptr;
	}
	*/
	
}

std::shared_ptr<Shader> HertzEngine::MakeDefaultShader()
{
	return ShaderManager::MakeShader();
}

std::vector<std::shared_ptr<HertzTexture>> HertzEngine::GetDefaultTexture()
{
	return TextureManager::MakeDefaultTextures();
}

std::shared_ptr<TextureManager> HertzEngine::GetTextureManager()
{
	return this->m_textureManager;
}

std::shared_ptr<Lightmanager> HertzEngine::GetLightManager()
{
	return this->m_lightManager;
}

std::shared_ptr<Meshmanager> HertzEngine::GetMeshMangr()
{
	if (manager)
	{
		return manager;

	}
	else
	{
		std::cerr << "Fatal error HertzEngine::GetMeshMangr: Mesh Manager was nullptr!" << std::endl;
		return nullptr;
	}
}


void HertzEngine::Update()
{
	if (!bShouldClose)
	{
		
		// DeltaTime
		double currentFrame = (glfwGetTime()); //get curent time
		fDeltaTime = currentFrame - fPrevFrame;//get time difference
		fPrevFrame = currentFrame; //set last frame as current time for next iteration



		//physics Step time
		m_SimulationAccumulator += fDeltaTime * m_PhysicsEngine->m_TimeScale;


		// UI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//messaging
		ProcessMessages();
		
		HertzInput::imouse_scroll_callback(GameWindow, 0, 0);
		HertzInput::imouse_callback(GameWindow);
		HertzInput::iprocessInput(GameWindow);

		//ImGui::ShowDemoWindow();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int physicsIterations = 0;

		while (m_PhysicsEngine->m_isSimulating && (m_PhysicsEngine->m_FastForward || m_SimulationAccumulator >= m_SimulationTimeStep) )
		{
			double ahh = 10.0;

			m_PhysicsEngine->Simulate(m_SimulationTimeStep);

			if (!m_PhysicsEngine->m_FastForward)
			{
				m_SimulationAccumulator -= m_SimulationTimeStep; 
			}

			else
			{
				m_PhysicsEngine->m_FastForwardDuration -= m_SimulationTimeStep;
				physicsIterations++;

				if (physicsIterations % 10000 == 0)
				{
					std::cout << "Remaining Duration: " << m_PhysicsEngine->m_FastForwardDuration << std::endl;

				}

				if (m_PhysicsEngine->m_FastForwardDuration <= 0.01)
				{
					m_PhysicsEngine->m_FastForward = false;
					break;
				}

			}

			

		}

		
		double alpha =  (m_SimulationAccumulator / m_SimulationTimeStep);
		if (alpha < 0.0)
			alpha = 0.0;
		if (alpha > 1.0)
			alpha = 1.0;


		for (auto en : m_EntityManager->m_entityList)
		{
			
			std::shared_ptr<Transform> trans = en->GetTransform();
			
			trans->m_interpolatedLocalPos = glm::mix(trans->m_prevLocalPos, trans->m_localPos, alpha);


		}
		


		m_editor->EditorUI(GameWindow);
		//del me
		/*
		if (!cam->m_LookAt)
		{
			cam->SetOrbitalTarget(entityTest->GetTransform(), 3, entityTest->GetName()->c_str());
			
		}
		*/
		glm::mat4 view = cam->GetViewMat4();

		//trailTest->Update(fDeltaTime);
		for (auto& col : m_PhysicsEngine->m_colliderList)
		{
			if (col->m_type == Sphere)
			{
				std::shared_ptr<SphereCollider> sphere = std::static_pointer_cast<SphereCollider>(col);
				if (sphere->m_trail->isUpdating)
				{
					sphere->m_trail->Draw();

				}
			}
		}


		//entityTest->GetTransform()->GetPos() += 0.01f;


		cam->CameraUpdate();
		//Render

		
		m_shaderManager->UpdateShaders(cam->GetProjection(), view, cam->
			vPos, cam, m_lightManager);

		m_EntityManager->Update(HertzEngine::DeltaTime(), cam);

		
		/*
		DefaultShader->Use();
		DefaultShader->setMat4("projection", projection);
		DefaultShader->setMat4("view", view);
		DefaultShader->setVec3("viewPos", cam->vPos);
		*/


		manager->Render(); //does nothing atm.





		//End Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(GameWindow);
		glfwPollEvents();
	}

	/*ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();*/
}

void HertzEngine::MessageHandling()
{
	/*
	while (auto msg = messagequeue.Pop())
	{
		switch (msg->m_type)
		{
		case MessageType::LoadOBJ:
		{
			ObjLoadedMessage* resourcesMsg = dynamic_cast<ObjLoadedMessage*>(msg.get());
			if (resourcesMsg)
			{
				std::shared_ptr<Mesh> mesh = resourcesMsg->GetLoadedMesh();
				Meshmanager* mngr = HertzEngine::GetMeshMangr();
				mngr->AddMesh(mesh);

				

			}
		}
		}
	}
	*/
	
}



void HertzEngine::ProcessMessages()
{

	while (auto msg = messagequeue.Pop())
	{
		switch (msg->m_type)
		{
		case MessageType::LoadOBJ:
		{

			std::shared_ptr<ObjMessage> objmsg = std::static_pointer_cast<ObjMessage>(msg);


			if (objmsg)
			{
				std::string path = objmsg->m_tPath;
				std::cout << "[HertzEngine::ProcessMessages] LoadObj Request Found... " << path << std::endl;

				std::thread([this, path]()
				{
						std::cout << "[HertzEingine::ProcessMessages] Worker thread loading obj..." << std::endl;
						std::shared_ptr<ObjData> data = ObjLoader::GetObjData(path.c_str());
						if (data)
						{

							messagequeue.Push(std::make_shared<ObjLoadedMessage>(data, path.c_str()));
							std::cout << "[HertzEngine::ProcessMessages] Worker thread success!!" << std::endl;
						}


				}).detach();
				
			}
			break;
		}

		case MessageType::LoadedResource:
		{
			std::shared_ptr<ObjLoadedMessage> loadedMsg = std::static_pointer_cast<ObjLoadedMessage>(msg);

			if (loadedMsg && loadedMsg->GetObjData())
			{
				if (HertzEngine::GetMeshMangr())
				{
					std::shared_ptr<Meshmanager> Manager = HertzEngine::GetMeshMangr();
					manager->AddMeshByData(loadedMsg->GetObjData(), loadedMsg->m_sPath.c_str());


					std::cout << "[HertzEngine::ProcessMessages] Added Mesh to manager! :)" << std::endl;
				}

			}

			break;
		}
		case MessageType::MipMap:
		{
			
			std::shared_ptr<MipMapMessage> mip = std::static_pointer_cast<MipMapMessage>(msg);

			if (mip)
			{
				TextureManager::UpdateMipMap(mip->GetSetting());
			}
			break;
		}


		}
	}
}

void HertzEngine::WorkerThreadOBJ()
{
	/*
	while (auto msg = messagequeue.PopBlock())
	{
		switch (msg->m_type)
		{
			case MessageType::LoadOBJ:
			{
				std::shared_ptr<ObjMessage> objMsg = std::dynamic_pointer_cast<ObjMessage>(msg); //continue here
				if (objMsg)
				{
					std::cout << "Thread Processing mesh... " << std::endl;
					std::shared_ptr<Mesh> mesh = ObjLoader::LoadObjData(objMsg->m_tPath.c_str());

					std::shared_ptr<ObjLoadedMessage> hasLoadedmsg = std::make_shared<ObjLoadedMessage>(mesh);
					messagequeue.Push(hasLoadedmsg);
					
					
					
					
				}
			}
		}
	}
	*/
}

// Note. The DeltaTime multiplier starts off at 150 time scale. 

std::shared_ptr<EntityManager> HertzEngine::GetEntityManager()
{
	return this->m_EntityManager;
}

std::shared_ptr<PhysicsEngine2> HertzEngine::GetPhysicsEngine()
{
	return this->m_PhysicsEngine;
}

std::shared_ptr<ShaderManager> HertzEngine::GetShaderManager()
{
	return this->m_shaderManager;
}

std::shared_ptr<HertzEditor> HertzEngine::GetEditor()
{
	return this->m_editor;
}




