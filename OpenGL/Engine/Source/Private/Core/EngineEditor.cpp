#include "PCH.h"
#include "EngineEditor.h"
#include "Window.h"
#include "WindowEditorMain.h"
#include "Scene.h"

EngineEditor::EngineEditor(const ObjectInitData& _data) : Engine(_data)
{

}

void EngineEditor::Init(HINSTANCE _handle)
{
	Engine::Init(_handle);

	Window::CreateWindowClass(this, "Test");

	Window::NewWindowParams p;
	p.windowClass = "Test";
	p.title = "Test";
	p.x = 0;
	p.y = 0;
	p.width = 1200;
	p.height = 800;
	WindowEditorMain* window = Window::Create<WindowEditorMain>(this, p);
	window->SetAsMainWindow();

	Scene* scene = Scene::Create(this);
	scene->SetAsActiveScene();

	window->RegisterScene(scene);
}

void EngineEditor::Update(float _dt)
{
	Engine::Update(_dt);
}

void EngineEditor::Shutdown()
{
	Engine::Shutdown();
}
