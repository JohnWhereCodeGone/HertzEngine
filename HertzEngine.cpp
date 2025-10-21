#include "HertzEngine.h"
#include "input/hertzinputs.h" 
#include "../UI/HertzEditor.h"
#include <thread>
#include "../Threading/MipMapMessage.h"



std::shared_ptr<Shader> HertzEngine::DefaultShader = nullptr;

float HertzEngine::fDeltaTime = 0.0f;

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
	manager = new Meshmanager();
	m_EntityManager = std::make_shared<EntityManager>();
	
	


	//Cam Setup
	cam = new Camera();
	projection = glm::perspective(glm::radians(cam->fZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	
	fDeltaTime = 0.0f;
	
	// Shader Setup:
	GameWindow = GameInit();
	DefaultShader = ShaderManager::MakeShader();
	DefaultShader->setFloat("material.shine", 264.f);
	
	//initialize view
	
}

GLFWwindow* HertzEngine::GameInit()
{
	// Window Setup
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //getproc = current function pointers for OS.
		glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //used to give the GUI system some ideas of how this window wants to be treated. shuts down if opengl v3 ain't on pc.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
#endif

	GameWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GAMEE WINDOW", NULL, NULL);

	if (!GameWindow)
	{
		std::cout << "window creation failed." << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(GameWindow);
	gladLoadGL();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetWindowUserPointer(GameWindow, this);

	glfwSetFramebufferSizeCallback(GameWindow, framebuffer_size_callback);
	glfwSetScrollCallback(GameWindow, HertzInput::imouse_scroll_callback);
	glfwSetCursorPosCallback(GameWindow, HertzInput::imouse_callback);

	glfwSetInputMode(GameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowOpacity(GameWindow, 0.8f);

	glEnable(GL_DEPTH_TEST);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	ImGui_ImplGlfw_InitForOpenGL(GameWindow, true);
	ImGui_ImplOpenGL3_Init();


	//threading



	// Default Shader.

	return GameWindow;
}

const float HertzEngine::DeltaTime()
{
	return fDeltaTime;
}



Camera* HertzEngine::GetCam()
{
	if (cam)
		return cam;
	else
		std::cerr << "GetCam: Camera was null " << std::endl;
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
	using ShaderPtr = std::shared_ptr<Shader>;

	ShaderPtr shad = std::make_shared<Shader>();

	if (shad)
	{
		shad->setFloat("material.shine", 264.f);
		return shad;

	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<HertzTexture>> HertzEngine::GetDefaultTexture()
{
	std::vector<std::shared_ptr<HertzTexture>> textures;

	std::shared_ptr<HertzTexture> diffuse = TextureManager::LoadTexture("./texture./container2.png", TextureType::Diffuse, true);
	std::shared_ptr<HertzTexture> specular = TextureManager::LoadTexture("./texture./container2_specular.png", TextureType::Specular, true);


	diffuse->m_type = "texture_diffuse";
	specular->m_type = "texture_specular";

	diffuse->m_texturetype = TextureType::Diffuse;
	specular->m_texturetype = TextureType::Specular;

	textures.push_back(diffuse);
	textures.push_back(specular);

	return textures;
}

Meshmanager* HertzEngine::GetMeshMangr()
{
	if (manager)
	{
		return manager;

	}
	else
	{
		std::cerr << "Fatal error HertzEngine::GetMeshMangr: Mesh Manager was nullptr!" << std::endl;
	}
}


void HertzEngine::Update()
{
	if (!bShouldClose)
	{
		
		// DeltaTime
		float currentFrame = static_cast<float>(glfwGetTime()); //get curent time
		fDeltaTime = currentFrame - fPrevFrame;//get time difference
		fPrevFrame = currentFrame; //set last frame as current time for next iteration

		//messaging
		ProcessMessages();

		// UI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		HertzEditor::EditorUI(GameWindow);

		HertzInput::iprocessInput(GameWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		m_EntityManager->Update(HertzEngine::DeltaTime());
		//Render

		glm::mat4 view = cam->GetViewMat4();
		
		m_shaderManager->UpdateShaders(projection, view, cam->vPos);
		
		/*
		DefaultShader->Use();
		DefaultShader->setMat4("projection", projection);
		DefaultShader->setMat4("view", view);
		DefaultShader->setVec3("viewPos", cam->vPos);
		*/


		manager->Render();

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
					Meshmanager* Manager = HertzEngine::GetMeshMangr();
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

std::shared_ptr<EntityManager> HertzEngine::GetEntityManager()
{
	return this->m_EntityManager;
}




