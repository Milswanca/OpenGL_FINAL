#pragma once
#include "Vector4.h"

struct Vector3;
struct Quaternion;

struct Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(const float* _vals);
	Matrix4x4(const Vector4 _c1, const Vector4 _c2, const Vector4 _c3, const Vector4 _c4);

	Vector4& operator[](const size_t _index);
	Vector4 operator[](const size_t _index) const;

	Matrix4x4 Inverse() const;
	Matrix4x4 OrthoInverse() const;

	friend Vector4 operator*(const Matrix4x4& _lhs, const Vector4& _rhs);
	friend Matrix4x4 operator*(const Matrix4x4& _lhs, const Matrix4x4& _rhs);

	static Matrix4x4 TRS(const Vector3 _t, const Quaternion _r);
	static Matrix4x4 Translation(const Vector3 _position);
	static Matrix4x4 Rotation(const Quaternion _rotation);
	static Matrix4x4 Perspective(const float _ar, const float _fov, const float _near, const float _far);
	static Matrix4x4 LookAt(const Vector3 _position, const Vector3 _lookAtPos, const Vector3 _up);

	const float* GetData() const;

private:
	Vector4 mat[4];
};

