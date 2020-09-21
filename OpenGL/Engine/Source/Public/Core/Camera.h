#pragma once
#include "Actor.h"

class CameraComponent;

class Camera : public Actor
{
public:
	Camera(const ObjectInitData& _data);

	void SetProjection(const float _ar, const float _fov, const float _nearClip, const float _farClip);
	void SetView(const Vector3 _position, const Vector3 _forward, const Vector3 _up);

	virtual void Update(const float _dt) override;

	Matrix4x4 GetProjection() const;
	Matrix4x4 GetView() const;
	Matrix4x4 GetProjectionView() const;

private:
	CameraComponent* m_camera;
	Vector3 m_lookAtPos;
	Vector3 m_viewPos;
};

