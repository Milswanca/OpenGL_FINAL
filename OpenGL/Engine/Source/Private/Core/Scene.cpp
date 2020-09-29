#include "PCH.h"
#include "Scene.h"
#include "Actor.h"
#include "Engine.h"
#include "InputSystem.h"

Scene::Scene(const ObjectInitData& _data) : Object(_data)
{
	m_inputSystem = SpawnActor<InputSystem>();
}

Scene* Scene::Create(Object* _outer)
{
	Scene* scene = _outer->GetEngine()->NewObject<Scene>(_outer);
	_outer->GetEngine()->RegisterScene(scene);

	return scene;
}

void Scene::SetAsActiveScene()
{
	GetEngine()->SetAsActiveScene(this);
}

void Scene::BecameActiveScene()
{

}

void Scene::RemovedAsActiveScene()
{

}

void Scene::UpdateScene(const float _dt)
{
	for (int i = 0; i < m_actors.size(); ++i)
	{
		m_actors[i]->Update(_dt);
	}

	for (int i = 0; i < m_actors.size(); ++i)
	{
		m_actors[i]->PostUpdate(_dt);
	}
}

Scene* Scene::GetScene()
{
	return this;
}

const Scene* Scene::GetScene() const
{
	return this;
}

unsigned int Scene::GetNumActors() const
{
	return m_actors.size();
}

Actor* Scene::GetActor(unsigned int _index) const
{
	return m_actors[_index];
}

InputSystem* Scene::GetInputSystem() const
{
	return m_inputSystem;
}