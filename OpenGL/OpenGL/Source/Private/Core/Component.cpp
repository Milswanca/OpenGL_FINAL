#include "PCH.h"
#include "Component.h"
#include "Transform.h"
#include "Engine.h"

Component::Component(const ObjectInitData& _data) : Object(_data)
{
	m_trans = GetEngine()->NewObject<Transform>(this);
	m_actor = reinterpret_cast<Actor*>(_data.outer);
}

Component::~Component()
{
	delete m_trans;
}

Actor* Component::GetActor() const
{
	return m_actor;
}

Transform* Component::GetTrans() const
{
	return m_trans;
}

void Component::Rotate(const Quaternion& _rotation)
{
	GetTrans()->Rotate(_rotation);
}

void Component::Rotate(const float _angle, const Vector3& _axis)
{
	GetTrans()->Rotate(_angle, _axis);
}

void Component::Rotate(const Vector3& _euler)
{
	GetTrans()->Rotate(_euler);
}

void Component::Translate(const Vector3& _trans)
{
	GetTrans()->Translate(_trans);
}

void Component::SetLocalPosition(const Vector3& _position)
{
	GetTrans()->SetLocalPosition(_position);
}

void Component::SetLocalRotation(const Quaternion& _rotation)
{
	GetTrans()->SetLocalRotation(_rotation);
}

void Component::SetWorldPosition(const Vector3& _position)
{
	GetTrans()->SetWorldPosition(_position);
}

void Component::SetWorldRotation(const Quaternion& _rotation)
{
	GetTrans()->SetWorldRotation(_rotation);
}

Vector3 Component::GetLocalPosition() const
{
	return GetTrans()->GetLocalPosition();
}

Quaternion Component::GetLocalRotation() const
{
	return GetTrans()->GetLocalRotation();
}

Vector3 Component::GetWorldPosition() const
{
	return GetTrans()->GetWorldPosition();
}

Quaternion Component::GetWorldRotation() const
{
	return GetTrans()->GetWorldRotation();
}

Matrix4x4 Component::GetLocalToWorld() const
{
	return GetTrans()->GetLocalToWorld();
}

Matrix4x4 Component::GetWorldToLocal() const
{
	return GetTrans()->GetWorldToLocal();
}