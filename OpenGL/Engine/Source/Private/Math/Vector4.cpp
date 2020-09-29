#include "PCH.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"

#include "Serialization.h"

Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(Vector3 _xyz, float _w)
{
	x = _xyz.x;
	y = _xyz.y;
	z = _xyz.z;
	w = _w;
}

Vector4::Vector4(const float _x, const float _y, const float _z, const float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vector4 Vector4::operator*(const float _val) const
{
	return Vector4(
		x * _val,
		y * _val,
		z * _val,
		w * _val
	);
}

Vector4 Vector4::operator+(const Vector4& _rhs) const
{
	return Vector4(
		x + _rhs.x,
		y + _rhs.y,
		z + _rhs.z,
		w + _rhs.w
	);
}

Vector4 Vector4::operator-() const
{
	return Vector4(
		-x,
		-y,
		-z,
		-w
	);
}

void Vector4::operator=(const Vector3& _val)
{
	x = _val.x;
	y = _val.y;
	z = _val.z;
	w = 0.0f;
}

float& Vector4::operator[](const size_t _index)
{
	return *(&x + _index);
}

float Vector4::operator[](const size_t _index) const
{
	return *(&x + _index);
}

Vector4::operator Vector3() const
{
	return Vector3(x, y, z);
}

Serializer& operator<<(Serializer& _os, const Vector4& _v)
{
	_os.Write((void*)&_v, sizeof(Vector4));
	return _os;
}

Serializer& operator>>(Serializer& _is, Vector4& _v)
{
	_is >> _v.x;
	_is >> _v.y;
	_is >> _v.z;
	_is >> _v.w;

	return _is;
}