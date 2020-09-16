#include "PCH.h"
#include "Object.h"

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