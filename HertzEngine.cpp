#include "HertzEngine.h"
#include "input/hertzinputs.h" 
#include "../UI/HertzEditor.h"


Shader* HertzEngine::DefaultShader = nullptr;
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
	

	//Cam Setup
	cam = new Camera();
	projection = glm::perspective(glm::radians(cam->fZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	
	fDeltaTime = 0.0f;
	
	// Shader Setup:
	GameWindow = GameInit();
	DefaultShader = new Shader();
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

Shader* HertzEngine::GetDefaultShader()
{
	if (DefaultShader)
	{
		return DefaultShader;

	}
	else
	{
		std::cerr << "Default shader was nullptr" << std::endl;
		return nullptr;
	}
}

Meshmanager* HertzEngine::GetMeshMangr()
{
	if (manager)
	{
		return manager;

	}
	else
	{
		std::cerr << "Fatal error: Mesh Manager was nullptr!" << std::endl;
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

		// UI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();

		HertzInput::iprocessInput(GameWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Render

		glm::mat4 view = cam->GetViewMat4();
		
		HertzEditor::EditorUI(GameWindow);

		DefaultShader->Use();
		DefaultShader->setMat4("projection", projection);
		DefaultShader->setMat4("view", view);
		DefaultShader->setVec3("viewPos", cam->vPos);


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

