#include "PCH.h"
#include "Transform.h"

Transform::Transform(const ObjectInitData& _data) : Object(_data)
{
	m_parent = nullptr;
	m_position = Vector3();
	m_children = std::vector<Transform*>();

	UpdateTransform();
}

void Transform::SetParent(Transform* _parent)
{
	if (_parent == this)
		return;

	m_parent = _parent;
	m_parent->AddChild(this);
}

void Transform::AddChild(Transform* _child)
{
	m_children.push_back(_child);
}

void Transform::Rotate(const Quaternion& _rotation)
{
	m_rotation *= _rotation;
	UpdateTransform();
}

void Transform::Rotate(const float _angle, const Vector3& _axis)
{
	m_rotation *= Quaternion::AngleAxis(_angle, _axis);
	UpdateTransform();
}

void Transform::Rotate(const Vector3& _euler)
{
	m_rotation *= Quaternion::Euler(_euler);
	UpdateTransform();
}

void Transform::Translate(const Vector3& _trans)
{
	m_position += _trans;
	UpdateTransform();
}

void Transform::SetLocalPosition(const Vector3& _position)
{
	m_position = _position;
	UpdateTransform();
}

void Transform::SetLocalRotation(const Quaternion& _rotation)
{
	m_rotation = _rotation;
	UpdateTransform();
}

void Transform::SetWorldPosition(const Vector3& _position)
{
	m_position += _position - GetWorldPosition();
	UpdateTransform();
}

void Transform::SetWorldRotation(const Quaternion& _rotation)
{

}

Vector3 Transform::GetWorldPosition() const
{
	return m_localToWorld[3];
}

Quaternion Transform::GetWorldRotation() const
{
	return Quaternion::LookAt(m_localToWorld[2], m_localToWorld[1]);
}

Vector3 Transform::GetLocalPosition() const
{
	return m_position;
}

Quaternion Transform::GetLocalRotation() const
{
	return m_rotation;
}

Matrix4x4 Transform::GetLocalToWorld() const
{
	return m_localToWorld;
}

Matrix4x4 Transform::GetWorldToLocal() const
{
	return m_worldToLocal;
}

void Transform::UpdateTransform()
{
	Matrix4x4 trs = Matrix4x4::TRS(m_position, m_rotation);

	Matrix4x4 parentWorldToLocal = Matrix4x4();
	Matrix4x4 parentLocalToWorld = Matrix4x4();

	if (m_parent != nullptr)
	{
		parentLocalToWorld = m_parent->GetLocalToWorld();
	}
	
	m_localToWorld = trs * parentLocalToWorld;
	m_worldToLocal = m_localToWorld.Inverse();

	for (size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->UpdateTransform();
	}
}