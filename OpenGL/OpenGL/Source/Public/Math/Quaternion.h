#pragma once
struct Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(const Vector3 _axis, const float _w);

	float Magnitude() const;
	void Normalize();
	Quaternion Normalized() const;

	void operator*=(const Quaternion& _rhs);
	Quaternion operator*(const Quaternion& _rhs) const;
	
	static Quaternion Euler(const Vector3 _euler);
	static Quaternion LookAt(const Vector3 _forward, const Vector3 _up);
	static Quaternion AngleAxis(const float _a, const Vector3 _axis);

	Matrix4x4 ToMatrix() const;
};

