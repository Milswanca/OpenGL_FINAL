#include "PCH.h"
#include "Engine.h"
#include "Program.h"
#include "TimeManager.h"

#include "Window.h"
#include "Actor.h"
#include "Scene.h"

Engine::Engine(const ObjectInitData& _data) : Object(_data)
{

}

void Engine::Init(HINSTANCE _handleInstance)
{
	m_handleInstance = _handleInstance;

	TimeManager::Init();
}

void Engine::RegisterScene(Scene* _scene)
{
	m_scenes.push_back(_scene);
}

void Engine::SetAsActiveScene(Scene* _scene)
{
	if (m_activeScene != nullptr)
	{
		m_activeScene->RemovedAsActiveScene();
	}

	m_activeScene = _scene;
	
	if (m_activeScene != nullptr)
	{
		m_activeScene->BecameActiveScene();
	}
}

void Engine::SetMainWindow(Window* _window)
{
	m_mainWindow = _window;
}

void Engine::Run()
{
	while (true)
	{
		TimeManager::Update();
		float dt = TimeManager::GetDeltaTime();

		Update(dt);
	}
}

void Engine::Update(float _dt)
{
	for (int i = 0; i < m_scenes.size(); ++i)
	{
		m_scenes[i]->UpdateScene(_dt);
	}

	for (int i = 0; i < m_windows.size(); ++i)
	{
		Window* w = m_windows[i];
		bool msg = w->Update();

		///Close
		if (msg == false && w == m_mainWindow)
		{
			return;
		}
	}
}

void Engine::RenderScene(Scene* _scene)
{
	if (_scene == nullptr)
		return;

	for (int i = 0; i < _scene->GetNumActors(); ++i)
	{
		_scene->GetActor(i)->Render();
	}
}

void Engine::Shutdown()
{

}

HINSTANCE Engine::GetHandleInstance() const
{
	return m_handleInstance;
}

Engine* Engine::GetEngine()
{
	return this;
}

const Engine* Engine::GetEngine() const
{
	return this;
}

Scene* Engine::GetActiveScene() const
{
	return m_activeScene;
}

void Engine::RegisterWindow(Window* _window)
{
	m_windows.push_back(_window);
}

void Engine::WindowDestroyed(Window* _window)
{
	//m_windows.remove(_window);
}