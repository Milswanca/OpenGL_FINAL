#pragma once
#include "Object.h"
#include "Engine.h"

class Component;

class Actor : public Object
{
public:
	Actor(const ObjectInitData& _data);

	template<typename T>
	T* AddComponent(Component* _parent)
	{
		T* component = GetEngine()->NewObject<T>(this);

		Component* comp = reinterpret_cast<Component*>(component);
		Component* parent = _parent != nullptr ? _parent : m_rootComponent;
		AddComponentImpl(comp, parent);

		m_components.push_back(comp);

		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			T* comp = static_cast<T*>(m_components[i]);

			if (comp != nullptr)
			{
				return comp;
			}
		}

		return nullptr;
	}

	virtual void Start();
	virtual void Update(const float _dt);
	virtual void End();

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

	Component* GetRootComponent() const;

private:
	void AddComponentImpl(Component* _component, Component* _parent);

	Component* m_rootComponent;
	std::vector<Component*> m_components;
};

