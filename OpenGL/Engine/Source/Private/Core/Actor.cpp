#include "PCH.h"
#include "Actor.h"
#include "Component.h"
#include "Transform.h"

Actor::Actor(const ObjectInitData& _data) : Object(_data)
{
	m_rootComponent = AddComponent<Component>(nullptr);
}

void Actor::AddComponentImpl(Component* _component, Component* _parent)
{
	if (_parent != nullptr)
	{
		_component->GetTrans()->SetParent(_parent->GetTrans());
	}
}

void Actor::Start()
{

}

void Actor::Update(const float _dt)
{

}

void Actor::End()
{

}

void Actor::Rotate(const Quaternion& _rotation)
{
	GetRootComponent()->Rotate(_rotation);
}

void Actor::Rotate(const float _angle, const Vector3& _axis)
{
	GetRootComponent()->Rotate(_angle, _axis);
}

void Actor::Rotate(const Vector3& _euler)
{
	GetRootComponent()->Rotate(_euler);
}

void Actor::Translate(const Vector3& _trans)
{
	GetRootComponent()->Translate(_trans);
}

void Actor::SetLocalPosition(const Vector3& _position)
{
	GetRootComponent()->SetLocalPosition(_position);
}

void Actor::SetLocalRotation(const Quaternion& _rotation)
{
	GetRootComponent()->SetLocalRotation(_rotation);
}

void Actor::SetWorldPosition(const Vector3& _position)
{
	GetRootComponent()->SetWorldPosition(_position);
}

void Actor::SetWorldRotation(const Quaternion& _rotation)
{
	GetRootComponent()->SetWorldRotation(_rotation);
}

Vector3 Actor::GetLocalPosition() const
{
	return GetRootComponent()->GetLocalPosition();
}

Quaternion Actor::GetLocalRotation() const
{
	return GetRootComponent()->GetLocalRotation();
}

Vector3 Actor::GetWorldPosition() const
{
	return GetRootComponent()->GetWorldPosition();
}

Quaternion Actor::GetWorldRotation() const
{
	return GetRootComponent()->GetWorldRotation();
}

Matrix4x4 Actor::GetLocalToWorld() const
{
	return GetRootComponent()->GetLocalToWorld();
}

Matrix4x4 Actor::GetWorldToLocal() const
{
	return GetRootComponent()->GetWorldToLocal();
}

Component* Actor::GetRootComponent() const
{
	return m_rootComponent;
}