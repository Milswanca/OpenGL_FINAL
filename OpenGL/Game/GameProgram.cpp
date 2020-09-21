#include "PCH.h"
#include "GameProgram.h"

#include "Shader.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector4.h"
#include "Transform.h"
#include "Material.h"

#include "Camera.h"
#include "Engine.h"
#include "TimeManager.h"
#include "AssetLoader.h"
#include "Mesh.h"

GameProgram::GameProgram(const ObjectInitData& _data) : Program(_data)
{

}

GameProgram::~GameProgram()
{

}

void GameProgram::Start()
{
	Program::Start();

	m_transform = GetEngine()->NewObject<Transform>(this);
	m_mesh = AssetLoader::LoadAsset<Mesh>(this, "Assets/Meshes/breakfast_room/breakfast_room.obj");

	m_material = AssetLoader::LoadAsset<Material>(this, "Assets/Materials/Material.mat");
	m_material->Bind();
	m_material->SetVector3("lightPos", Vector3(5.0f, 20.0f, 5.0f));

	m_camera = GetEngine()->SpawnActor<Camera>(this);
	m_camera->SetProjection(800.0f / 600.0f, 45.0f, 0.1f, 300.0f);
	m_camera->SetWorldPosition(Vector3(0.0f, 0.0f, 30.0f));
}

void GameProgram::Update(const float _deltaTime)
{
	Program::Update(_deltaTime);

	m_transform->Rotate(0.1f * _deltaTime, Vector3(0.0f, 1.0f, 0.0f));

	m_material->SetMatrix("Projection", m_camera->GetProjection());
	m_material->SetMatrix("View", m_camera->GetView());

	m_material->SetMatrix("Model", m_transform->GetWorldToLocal());

	int err = glGetError();
	glBindVertexArray(m_mesh->GetVAO());
	err = glGetError();

	for (int i = 0; i < m_mesh->GetNumShapes(); ++i)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->GetEBO(i));
		glDrawElements(GL_TRIANGLES, m_mesh->GetNumIndices(i), GL_UNSIGNED_INT, 0);
	}
}

void GameProgram::End()
{
	Program::End();
}