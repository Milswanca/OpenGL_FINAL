#include "PCH.h"
#include "Math/Vector3.h"

#include "Serialization.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector3::Normalize()
{
	float oneOverLen = 1.0f / Length();
	x *= oneOverLen;
	y *= oneOverLen;
	z *= oneOverLen;
}

Vector3 Vector3::Normalized() const
{
	float oneOverLen = 1.0f / Length();

	Vector3 ret = *this * oneOverLen;
	ret.Normalize();

	return ret;
}

void Vector3::OrthoNormalize(Vector3& _forward, Vector3& _up)
{
	_up.Normalize();
	_forward = (_forward - Vector3::Project(_up, _forward)).Normalized();
}

Vector3 Vector3::Project(const Vector3& _forward, const Vector3& _up)
{
	return Dot(_forward, _up) * _up * (1.0f / _forward.SqrLength());
}

Vector3 Vector3::Cross(const Vector3& _v1, const Vector3& _v2)
{
	Vector3 v;
	v.x = (_v1.y * _v2.z) - (_v1.z * _v2.y);
	v.y = (_v1.z * _v2.x) - (_v1.x * _v2.z);
	v.z = (_v1.x * _v2.y) - (_v1.y * _v2.x);

	return v;
}

float Vector3::Dot(const Vector3& _v1, const Vector3& _v2)
{
	float product = 0.0f;
	product = (_v1.x * _v2.x) + (_v1.y * _v2.y) + (_v1.z * _v2.z);

	return product;
}

float Vector3::SqrLength() const
{
	return (x * x) + (y * y) + (z * z);
}

float Vector3::Length() const
{
	return sqrt(SqrLength());
}

Vector3::operator Vector4() const
{
	return Vector4(x, y, z, 0.0f);
}

float& Vector3::operator[](const size_t _index)
{
	return *(&x + _index);
}

float Vector3::operator[](const size_t _index) const
{
	return *(&x + _index);
}

void operator+=(Vector3& _lhs, const Vector3& _rhs)
{
	_lhs.x += _rhs.x;
	_lhs.y += _rhs.y;
	_lhs.z += _rhs.z;
}

Vector3 operator*(const Vector3& _lhs, const float _rhs)
{
	Vector3 v = _lhs;
	v.x *= _rhs;
	v.y *= _rhs;
	v.z *= _rhs;

	return v;
}

Vector3 operator*(const float _lhs, const Vector3& _rhs)
{
	return _rhs * _lhs;
}

Vector3 operator-(const Vector3& _lhs)
{
	return Vector3(-_lhs.x, -_lhs.y, -_lhs.z);
}

Vector3 operator-(const Vector3& _lhs, const Vector3& _rhs)
{
	Vector3 v = _lhs;
	v.x -= _rhs.x;
	v.y -= _rhs.y;
	v.z -= _rhs.z;

	return v;
}

Vector3 operator+(const Vector3& _lhs, const Vector3& _rhs)
{
	Vector3 v = _lhs;
	v.x += _rhs.x;
	v.y += _rhs.y;
	v.z += _rhs.z;

	return v;
}

Serializer& operator<<(Serializer& _os, const Vector3& _v)
{
	_os.Write((void*)&_v, sizeof(Vector3));
	return _os;
}

Serializer& operator>>(Serializer& _is, Vector3& _v)
{
	_is.Read(&_v, sizeof(Vector3));
	return _is;
}