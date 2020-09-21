#pragma once
#include "Object.h"

class Program;
class Actor;

class Engine : public Object
{
public:
	Engine(const ObjectInitData& _data);

	void Init();
	void Run();
	void Shutdown();

	GLFWwindow* CreateWindow(int _width, int _height, const char* _title);
	void SetViewport(int _x, int _y, int _width, int _height);

	GLFWwindow* GetMainWindow() const;

	template<typename T>
	T* NewObject(Object* _outer)
	{
		ObjectInitData data = ObjectInitData();
		data.engine = this;
		data.outer = _outer;

		T* o = new T(data);
		Object* obj = reinterpret_cast<Object*>(o);

		m_objects.push_back(obj);
		return o;
	}

	template<typename T>
	T* SpawnActor(Object* _outer)
	{
		T* a = NewObject<T>(_outer);
		Actor* actor = reinterpret_cast<Actor*>(a);
		actor->Start();

		m_actors.push_back(actor);
		return a;
	}

	template<typename T>
	T* SpawnProgram()
	{
		T* program = SpawnActor<T>(this);
		m_program = reinterpret_cast<Program*>(program);
		return program;
	}

	virtual const Engine* GetEngine() const override;

private:
	GLFWwindow* m_mainWindow;
	Program* m_program;

	std::vector<Actor*> m_actors;
	std::vector<Object*> m_objects;
};

