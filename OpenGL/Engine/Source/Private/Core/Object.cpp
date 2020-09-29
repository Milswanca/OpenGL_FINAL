#include "PCH.h"
#include "Object.h"
#include "Scene.h"

Object::Object(const ObjectInitData& _data)
{
	m_engine = _data.engine;
}

Engine* Object::GetEngine()
{
	return m_engine;
}

const Engine* Object::GetEngine() const
{
	return m_engine;
}

Scene* Object::GetScene()
{
	return nullptr;
}

const Scene* Object::GetScene() const
{
	return nullptr;
}

InputSystem* Object::GetInputSystem()
{
	return GetScene() != nullptr ? GetScene()->GetInputSystem() : nullptr;
}

const InputSystem* Object::GetInputSystem() const
{
	return GetScene() != nullptr ? GetScene()->GetInputSystem() : nullptr;
}