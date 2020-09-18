#pragma once
#include "Object.h"

class Transform;
class Actor;

class Component : public Object
{
public:
	Component(const ObjectInitData& _data);
	~Component();

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

	Actor* GetActor() const;
	Transform* GetTrans() const;

private:
	Transform* m_trans;
	Actor* m_actor;
};

