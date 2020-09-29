#pragma once
#include "Object.h"

class Actor;

class Scene : public Object
{
public:
	Scene(const ObjectInitData& _data);

	static Scene* Create(Object* _outer);

	void SetAsActiveScene();
	virtual Scene* GetScene() override;
	virtual const Scene* GetScene() const override;
	unsigned int GetNumActors() const;
	Actor* GetActor(unsigned int _index) const;
	InputSystem* GetInputSystem() const;

protected:
	void UpdateScene(const float _dt);

	virtual void BecameActiveScene();
	virtual void RemovedAsActiveScene();

private:
	std::vector<Actor*> m_actors;
	InputSystem* m_inputSystem;

public:
	template<typename T>
	T* SpawnActor()
	{
		T* ret = GetEngine()->NewObject<T>(this);
		Actor* actor = reinterpret_cast<Actor*>(ret);
		m_actors.push_back(actor);

		actor->Start();

		return ret;
	}

private:
	friend class Engine;
};

