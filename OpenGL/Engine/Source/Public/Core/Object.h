#pragma once

class Scene;
class InputSystem;

class Object
{
public:
	Object() = delete;
	Object(const ObjectInitData& _data);

	virtual Engine* GetEngine();
	virtual const Engine* GetEngine() const;

	virtual Scene* GetScene();
	virtual const Scene* GetScene() const;

	virtual InputSystem* GetInputSystem();
	virtual const InputSystem* GetInputSystem() const;

private:
	Engine* m_engine;
};

