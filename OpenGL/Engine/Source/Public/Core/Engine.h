#pragma once
#include "Object.h"

class Actor;
class Window;
class Scene;

class Engine : public Object
{
public:
	Engine(const ObjectInitData& _data);

	virtual void Init(HINSTANCE _handleInstance);
	void Run();
	virtual void Update(float _dt);
	/// <summary>
	/// Temporarily here
	/// </summary>
	void RenderScene(Scene* _scene);
	virtual void Shutdown();

	Scene* GetActiveScene() const;
	HINSTANCE GetHandleInstance() const;
	virtual Engine* GetEngine() override;
	virtual const Engine* GetEngine() const override;

private:
	void SetAsActiveScene(Scene* _scene);
	void RegisterScene(Scene* _scene);
	void SetMainWindow(Window* _window);
	void RegisterWindow(Window* _window);
	void WindowDestroyed(Window* _window);

private:
	Scene* m_activeScene;
	Window* m_mainWindow;

	std::vector<Scene*> m_scenes;
	std::vector<Window*> m_windows;
	std::vector<Object*> m_objects;

	HINSTANCE m_handleInstance;

public:
	template<typename T>
	T* NewObject(Object* _outer)
	{
		ObjectInitData data = ObjectInitData();
		data.engine = this;
		data.outer = _outer;
		data.scene = _outer->GetScene();

		T* o = new T(data);
		Object* obj = reinterpret_cast<Object*>(o);

		m_objects.push_back(obj);
		return o;
	}

	friend class Window;
	friend class Scene;
};

