#pragma once

struct Vector3;

struct Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float _x, float _y, float _z);

	void Normalize();
	Vector3 Normalized() const;
	float Length() const;
	float SqrLength() const;

	float GetX() const;
	float GetY() const;
	float GetZ() const;

	void SetX(const float _x);
	void SetY(const float _y);
	void SetZ(const float _z);

	static Vector3 Cross(const Vector3& _v1, const Vector3& _v2);
	static float Dot(const Vector3& _v1, const Vector3& _v2);
	static void OrthoNormalize(Vector3& _forward, Vector3& _up);
	static Vector3 Project(const Vector3& _forward, const Vector3& _up);

	operator Vector4() const;
	float& operator[](const size_t _index);
	float operator[](const size_t _index) const;

	friend void operator+=(Vector3& _lhs, const Vector3& _rhs);

	friend Vector3 operator*(const Vector3& _lhs, const float _rhs);
	friend Vector3 operator*(const float _lhs, const Vector3& _rhs);

	friend Vector3 operator-(const Vector3& _lhs);
	friend Vector3 operator-(const Vector3& _lhs, const Vector3& _rhs);
	friend Vector3 operator+(const Vector3& _lhs, const Vector3& _rhs);
};