#pragma once
#include "Actor.h"

class Material;
class Camera;
class Transform;
class Mesh;

class Program : public Actor
{
public:
	Program(const ObjectInitData& _data);
	~Program();

	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void End() override;

private:
	Material* m_material;
	Camera* m_camera;
	Mesh* m_mesh;

	Transform* m_transform;
};

