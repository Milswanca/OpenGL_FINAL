#pragma once
#include "Program.h"

class Material;
class Camera;
class Transform;
class Mesh;

class GameProgram : public Program
{
public:
	GameProgram(const ObjectInitData& _data);
	~GameProgram();

	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Render() override;
	virtual void End() override;

private:
	Material* m_material;
	Camera* m_camera;
	Mesh* m_mesh;

	Transform* m_transform;
};