#include "PCH.h"
#include "Camera.h"
#include "CameraComponent.h"

#include "Engine.h"

Camera::Camera(const ObjectInitData& _data) : Actor(_data)
{
	m_camera = AddComponent<CameraComponent>(GetRootComponent());
}

void Camera::SetProjection(const float _ar, const float _fov, const float _nearClip, const float _farClip)
{
	m_camera->SetProjection(_ar, _fov, _nearClip, _farClip);
}

void Camera::SetView(const Vector3 _position, const Vector3 _forward, const Vector3 _up)
{
	m_lookAtPos = _forward;
	m_viewPos = _position;
	m_camera->SetView(_position, _forward, _up);
}

void Camera::Update(const float _dt)
{
	Actor::Update(_dt);

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		Translate(Vector3(10.0f * _dt, 0.0f, 0.0f));
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		Translate(Vector3(-10.0f * _dt, 0.0f, 0.0f));
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		Translate(Vector3(0.0f, 0.0f, -10.0f * _dt));
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		Translate(Vector3(0.0f, 0.0f, 10.0f * _dt));
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		Translate(Vector3(0.0f, -10.0f * _dt, 0.0f));
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		Translate(Vector3(0.0f, 10.0f * _dt, 0.0f));
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		m_lookAtPos.x = (m_lookAtPos.x - 10.0f * _dt);
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		m_lookAtPos.x = (m_lookAtPos.x + 10.0f * _dt);
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		m_lookAtPos.y = (m_lookAtPos.y + 10.0f * _dt);
	}

	if (glfwGetKey(GetEngine()->GetMainWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		m_lookAtPos.y = (m_lookAtPos.y - 10.0f * _dt);
	}

	SetView(GetWorldPosition(), GetWorldPosition() + Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f));
}

Matrix4x4 Camera::GetProjection() const
{
	return m_camera->GetProjection();
}

Matrix4x4 Camera::GetView() const
{
	return m_camera->GetView();
}

Matrix4x4 Camera::GetProjectionView() const
{
	return m_camera->GetProjectionView();
}