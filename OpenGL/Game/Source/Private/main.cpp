#pragma once
#include "PCH.h"
#include "Engine.h"
#include "GameProgram.h"
#include "Window.h"
#include "Scene.h"
#include "WindowEditorMain.h"

#include "EngineEditor.h"

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
#if EDITOR
	ObjectInitData data;
	EngineEditor* engine = new EngineEditor(data);

	engine->Init(hInstance);
	engine->Run();
	engine->Shutdown();
#else
	ObjectInitData data;
	Engine* engine = new Engine(data);

	engine->Init(hInstance);

	Window::CreateWindowClass(engine, "Test");

	Window::NewWindowParams p;
	p.windowClass = "Test";
	p.title = "Test";
	p.x = 0;
	p.y = 0;
	p.width = 1200;
	p.height = 800;
	WindowEditorMain* window = Window::Create<WindowEditorMain>(engine, p);
	window->SetAsMainWindow();

	Scene* scene = Scene::Create(engine);
	scene->SetAsActiveScene();
	scene->SpawnActor<GameProgram>();

	window->RegisterScene(scene);

	engine->Run();
	engine->Shutdown();
#endif
}