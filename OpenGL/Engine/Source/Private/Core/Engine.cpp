#include "PCH.h"
#include "Engine.h"
#include "Program.h"
#include "TimeManager.h"

#include "Actor.h"

Engine::Engine(const ObjectInitData& _data) : Object(_data)
{

}

void Engine::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	TimeManager::Init();

	CreateWindow(1200, 800, "OpenGL Demo");
	glEnable(GL_DEPTH_TEST);

#if EDITOR
	m_program = SpawnProgram<Program>();
#endif

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void Engine::Run()
{
	if (m_mainWindow == NULL)
	{
		throw "Trying to run the engine but there has been no window created";
	}

	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(m_mainWindow))
	{
		TimeManager::Update();
		float dt = TimeManager::GetDeltaTime();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < m_actors.size(); ++i)
		{
			m_actors[i]->Update(dt);
		}


		glfwSwapBuffers(m_mainWindow);
		glfwPollEvents();
	}
}

void Engine::Shutdown()
{
	m_program = nullptr;

	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}

GLFWwindow* Engine::CreateWindow(int _width, int _height, const char* _title)
{
	GLFWwindow* window = glfwCreateWindow(_width, _height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	
	if (m_mainWindow == NULL)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "Failed to initialize GLAD";
		}

		m_mainWindow = window;
	}

	//SetViewport(0, 0, _width, _height);
	return window;
}

void Engine::SetViewport(int _x, int _y, int _width, int _height)
{
	glViewport(_x, _y, _width, _height);
}

GLFWwindow* Engine::GetMainWindow() const
{
	return m_mainWindow;
}

const Engine* Engine::GetEngine() const
{
	return this;
}