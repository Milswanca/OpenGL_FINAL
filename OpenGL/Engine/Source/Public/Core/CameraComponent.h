#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent(const ObjectInitData& _data);

	void SetProjection(const float _ar, const float _fov, const float _nearClip, const float _farClip);
	void SetView(const Vector3 _position, const Vector3 _forward, const Vector3 _up);

	Matrix4x4 GetProjection() const;
	Matrix4x4 GetView() const;
	Matrix4x4 GetProjectionView() const;

private:
	void UpdateProjectionView();

	Matrix4x4 m_projection;
	Matrix4x4 m_view;
	Matrix4x4 m_projectionView;
};

