#pragma once

struct Vector3;
class Serializer;

struct Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(Vector3 _xyz, float _w);
	Vector4(const float _x, const float _y, const float _z, const float _w);

	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetW() const;

	void SetX(const float _x);
	void SetY(const float _y);
	void SetZ(const float _z);
	void SetW(const float _w);

	void operator=(const Vector3& _rhs);
	Vector4 operator*(const float _rhs) const;
	Vector4 operator+(const Vector4& _rhs) const;
	Vector4 operator-() const;
	float& operator[](const size_t _index);
	float operator[](const size_t _index) const;

	operator Vector3() const;

	friend Serializer& operator<<(Serializer& _os, const Vector4& _v);
	friend Serializer& operator>>(Serializer& _os, Vector4& _v);
};

