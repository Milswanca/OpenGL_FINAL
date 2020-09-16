#include "PCH.h"
#include "Math/Quaternion.h"

Quaternion::Quaternion()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Quaternion::Quaternion(const Vector3 _xyz, const float _w)
{
	x = _xyz[0];
	y = _xyz[1];
	z = _xyz[2];
	w = _w;
}

Quaternion Quaternion::operator*(const Quaternion& _rhs) const
{
	return Quaternion(
		((((w * _rhs.x) + (x * _rhs.w)) + (y * _rhs.z)) - (z * _rhs.y)),
		((((w * _rhs.y) + (y * _rhs.w)) + (z * _rhs.x)) - (x * _rhs.z)),
		((((w * _rhs.z) + (z * _rhs.w)) + (x * _rhs.y)) - (y * _rhs.x)),
		((((w * _rhs.w) - (x * _rhs.x)) - (y * _rhs.y)) - (z * _rhs.z))
	);
}

void Quaternion::operator*=(const Quaternion& _rhs)
{
	*this = *this * _rhs;
}

Matrix4x4 Quaternion::ToMatrix() const
{
	float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
	qx = x;
	qy = y;
	qz = z;
	qw = w;
	qx2 = (qx + qx);
	qy2 = (qy + qy);
	qz2 = (qz + qz);
	qxqx2 = (qx * qx2);
	qxqy2 = (qx * qy2);
	qxqz2 = (qx * qz2);
	qxqw2 = (qw * qx2);
	qyqy2 = (qy * qy2);
	qyqz2 = (qy * qz2);
	qyqw2 = (qw * qy2);
	qzqz2 = (qz * qz2);
	qzqw2 = (qw * qz2);

	Matrix4x4 mat = Matrix4x4();
	mat[0] = Vector4(((1.0f - qyqy2) - qzqz2), (qxqy2 + qzqw2), (qxqz2 - qyqw2), 0.0f);
	mat[1] = Vector4((qxqy2 - qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 + qxqw2), 0.0f);
	mat[2] = Vector4((qxqz2 + qyqw2), (qyqz2 - qxqw2), ((1.0f - qxqx2) - qyqy2), 0.0f);

	return mat;
}

float Quaternion::Magnitude() const
{
	float result;
	result = (x * x);
	result = (result + (y * y));
	result = (result + (z * z));
	result = (result + (w * w));

	result = sqrt(result);
	return result;
}

void Quaternion::Normalize()
{
	float lenInv;
	lenInv = (1.0f / Magnitude());

	x = x * lenInv;
	y = y * lenInv;
	z = z * lenInv;
	w = w * lenInv;
}

Quaternion Quaternion::Normalized() const
{
	Quaternion q = *this;
	q.Normalize();

	return q;
}

Quaternion Quaternion::Euler(const Vector3 _euler)
{
	float cy = cos(_euler.x * 0.5f);
	float sy = sin(_euler.x * 0.5f);
	float cp = cos(_euler.y * 0.5f);
	float sp = sin(_euler.y * 0.5f);
	float cr = cos(_euler.z * 0.5f);
	float sr = sin(_euler.z * 0.5f);

	Quaternion ret;
	ret.w = cr * cp * cy + sr * sp * sy;
	ret.x = sr * cp * cy - cr * sp * sy;
	ret.y = cr * sp * cy + sr * cp * sy;
	ret.z = cr * cp * sy - sr * sp * cy;

	return ret;
}

Quaternion Quaternion::LookAt(const Vector3 _forward, const Vector3 _up)
{
	Vector3 w = Vector3::Cross(_forward, _up);
	Quaternion q = Quaternion(w.x, w.y, w.z, Vector3::Dot(_forward, _up));
	q.w += q.Magnitude();
	return q.Normalized();
}

Quaternion Quaternion::AngleAxis(const float _a, const Vector3 _axis)
{
	float s, c, angle;
	angle = (_a * 0.5f);
	s = std::sinf(angle);
	c = std::cosf(angle);
	return Quaternion((_axis * s), c);
}