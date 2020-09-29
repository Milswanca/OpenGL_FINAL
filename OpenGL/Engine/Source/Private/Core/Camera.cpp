#include "PCH.h"
#include "Camera.h"
#include "CameraComponent.h"

#include "Engine.h"
#include "InputSystem.h"

Camera::Camera(const ObjectInitData& _data) : Actor(_data)
{
	m_camera = AddComponent<CameraComponent>(GetRootComponent());
	m_speed = 100.0f;
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

	if (GetInputSystem()->IsKeyDown('W'))
	{
		SetWorldPosition(GetWorldPosition() + Vector3(0.0f, 0.0f, m_speed * _dt));
	}

	if (GetInputSystem()->IsKeyDown('S'))
	{
		SetWorldPosition(GetWorldPosition() + Vector3(0.0f, 0.0f, -m_speed * _dt));
	}

	if (GetInputSystem()->IsKeyDown('A'))
	{
		SetWorldPosition(GetWorldPosition() + Vector3(-m_speed * _dt, 0.0f, 0.0f));
	}

	if (GetInputSystem()->IsKeyDown('D'))
	{
		SetWorldPosition(GetWorldPosition() + Vector3(m_speed * _dt, 0.0f, 0.0f));
	}

	if (GetInputSystem()->IsKeyDown('Q'))
	{
		SetWorldPosition(GetWorldPosition() + Vector3(0.0f, -m_speed * _dt, 0.0f));
	}

	if (GetInputSystem()->IsKeyDown('E'))
	{
		SetWorldPosition(GetWorldPosition() + Vector3(0.0f, m_speed * _dt, 0.0f));
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