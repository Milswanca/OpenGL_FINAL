#include "PCH.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent(const ObjectInitData& _data) : Component(_data)
{

}

void CameraComponent::SetProjection(const float _ar, const float _fov, const float _nearClip, const float _farClip)
{
	m_projection = Matrix4x4::Perspective(_ar, _fov, _nearClip, _farClip);
	UpdateProjectionView();
}

void CameraComponent::SetView(const Vector3 _position, const Vector3 _forward, const Vector3 _up)
{
	m_view = Matrix4x4::LookAt(_position, _forward, _up);
	UpdateProjectionView();
}

Matrix4x4 CameraComponent::GetProjection() const
{
	return m_projection;
}

Matrix4x4 CameraComponent::GetView() const
{
	return m_view;
}

Matrix4x4 CameraComponent::GetProjectionView() const
{
	return m_projectionView;
}

void CameraComponent::UpdateProjectionView()
{
	m_projectionView = m_projection * m_view;
}