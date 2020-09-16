#pragma once
#include "Object.h"

class Transform : public Object
{
public:
	Transform(const ObjectInitData& _data);

	void SetParent(Transform* _parent);

	void Rotate(const Quaternion& _rotation);
	void Rotate(const float _angle, const Vector3& _axis);
	void Rotate(const Vector3& _euler);

	void Translate(const Vector3& _trans);

	void SetLocalPosition(const Vector3& _position);
	void SetLocalRotation(const Quaternion& _rotation);
	void SetWorldPosition(const Vector3& _position);
	void SetWorldRotation(const Quaternion& _rotation);

	Vector3 GetLocalPosition() const;
	Quaternion GetLocalRotation() const;

	Vector3 GetWorldPosition() const;
	Quaternion GetWorldRotation() const;

	Matrix4x4 GetLocalToWorld() const;
	Matrix4x4 GetWorldToLocal() const;

private:
	void UpdateTransform();

	void AddChild(Transform* _child);

	std::vector<Transform*> m_children;

	Vector3 m_position;
	Quaternion m_rotation;

	Matrix4x4 m_localToWorld;
	Matrix4x4 m_worldToLocal;

	Transform* m_parent;
};

