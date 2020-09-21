#include "PCH.h"
#include "Math/Matrix4x4.h"
#include "Math.h"

Matrix4x4::Matrix4x4()
{
	mat[0][0] = 1.0f; mat[1][0] = 0.0f; mat[2][0] = 0.0f; mat[3][0] = 0.0f;
	mat[0][1] = 0.0f; mat[1][1] = 1.0f; mat[2][1] = 0.0f; mat[3][1] = 0.0f;
	mat[0][2] = 0.0f; mat[1][2] = 0.0f; mat[2][2] = 1.0f; mat[3][2] = 0.0f;
	mat[0][3] = 0.0f; mat[1][3] = 0.0f; mat[2][3] = 0.0f; mat[3][3] = 1.0f;
}

Matrix4x4::Matrix4x4(const Vector4 _c1, const Vector4 _c2, const Vector4 _c3, const Vector4 _c4)
{
	mat[0] = _c1;
	mat[1] = _c2;
	mat[2] = _c3;
	mat[3] = _c4;
}

Matrix4x4::Matrix4x4(const float* _vals)
{
	for (int i = 0; i < 16; ++i)
	{
		mat[i % 4][i / 4] = _vals[i];
	}
}

Vector4& Matrix4x4::operator[](const size_t _index)
{
	if (_index < 0 || _index > 3)
		throw "Invalid Matrix4x4 accessor with index: " + _index;

	return mat[_index];
}

Vector4 Matrix4x4::operator[](const size_t _index) const
{
	if (_index < 0 || _index > 3)
		throw "Invalid Matrix4x4 accessor with index: " + _index;

	return mat[_index];
}

Vector4 operator*(const Matrix4x4& _lhs, const Vector4& _rhs)
{
	return Vector4(
		((((_lhs[0][0] * _rhs[0]) + (_lhs[1][0] * _rhs[1])) + (_lhs[2][0] * _rhs[2])) + (_lhs[3][0] * _rhs[3])),
		((((_lhs[0][1] * _rhs[0]) + (_lhs[1][1] * _rhs[1])) + (_lhs[2][1] * _rhs[2])) + (_lhs[3][1] * _rhs[3])),
		((((_lhs[0][2] * _rhs[0]) + (_lhs[1][2] * _rhs[1])) + (_lhs[2][2] * _rhs[2])) + (_lhs[3][2] * _rhs[3])),
		((((_lhs[0][3] * _rhs[0]) + (_lhs[1][3] * _rhs[1])) + (_lhs[2][3] * _rhs[2])) + (_lhs[3][3] * _rhs[3]))
	);
}

Matrix4x4 operator*(const Matrix4x4& _lhs, const Matrix4x4& _rhs)
{
	return Matrix4x4(
		_lhs * _rhs[0],
		_lhs * _rhs[1],
		_lhs * _rhs[2],
		_lhs * _rhs[3]
	);
}

Matrix4x4 Matrix4x4::TRS(const Vector3 _t, const Quaternion _r)
{
	Matrix4x4 t = Translation(_t);
	Matrix4x4 r = Rotation(_r);

	return r * t;
}

Matrix4x4 Matrix4x4::Translation(const Vector3 _translation)
{
	Matrix4x4 mat = Matrix4x4();
	mat[3] = Vector4(_translation, 1.0f);

	return mat;
}

Matrix4x4 Matrix4x4::Rotation(const Quaternion _rotation)
{
	return _rotation.ToMatrix();
}

Matrix4x4 Matrix4x4::Perspective(const float _ar, const float _fov, const float _near, const float _far)
{
	static const float VECTORMATH_PI_OVER_2 = 1.570796327f;

	float f, rangeInv;
	f = std::tanf(VECTORMATH_PI_OVER_2 - (0.5f * _fov));
	rangeInv = (1.0f / (_near - _far));

	return Matrix4x4(
		Vector4((f / _ar), 0.0f, 0.0f, 0.0f),
		Vector4(0.0f, f, 0.0f, 0.0f),
		Vector4(0.0f, 0.0f, ((_near + _far) * rangeInv), -1.0f),
		Vector4(0.0f, 0.0f, (((_near * _far) * rangeInv) * 2.0f), 0.0f)
	);
}

Matrix4x4 Matrix4x4::LookAt(const Vector3 _position, const Vector3 _lookAtPos, const Vector3 _up)
{
	Matrix4x4 m4EyeFrame;
	Vector3 v3X, v3Y, v3Z;
	v3Y = _up.Normalized();
	v3Z = (_position - _lookAtPos).Normalized();
	v3X = Vector3::Cross(v3Y, v3Z).Normalized();
	v3Y = Vector3::Cross(v3Z, v3X);
	m4EyeFrame = Matrix4x4(Vector4(v3X), Vector4(v3Y), Vector4(v3Z), Vector4(_position, 1.0f));
	return m4EyeFrame.OrthoInverse();
}

Matrix4x4 Matrix4x4::Inverse() const
{
	Vector4 res0, res1, res2, res3;
	float mA, mB, mC, mD, mE, mF, mG, mH, mI, mJ, mK, mL, mM, mN, mO, mP, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, detInv;
	mA = mat[0][0];
	mB = mat[0][1];
	mC = mat[0][2];
	mD = mat[0][3];
	mE = mat[1][0];
	mF = mat[1][1];
	mG = mat[1][2];
	mH = mat[1][3];
	mI = mat[2][0];
	mJ = mat[2][1];
	mK = mat[2][2];
	mL = mat[2][3];
	mM = mat[3][0];
	mN = mat[3][1];
	mO = mat[3][2];
	mP = mat[3][3];
	tmp0 = ((mK * mD) - (mC * mL));
	tmp1 = ((mO * mH) - (mG * mP));
	tmp2 = ((mB * mK) - (mJ * mC));
	tmp3 = ((mF * mO) - (mN * mG));
	tmp4 = ((mJ * mD) - (mB * mL));
	tmp5 = ((mN * mH) - (mF * mP));
	res0.x = ((((mJ * tmp1) - (mL * tmp3)) - (mK * tmp5)));
	res0.y = ((((mN * tmp0) - (mP * tmp2)) - (mO * tmp4)));
	res0.z = ((((mD * tmp3) + (mC * tmp5)) - (mB * tmp1)));
	res0.w = ((((mH * tmp2) + (mG * tmp4)) - (mF * tmp0)));
	detInv = (1.0f / ((((mA * res0.x) + (mE * res0.y)) + (mI * res0.z)) + (mM * res0.w)));
	res1.x = ((mI * tmp1));
	res1.y = ((mM * tmp0));
	res1.z = ((mA * tmp1));
	res1.w = ((mE * tmp0));
	res3.x = ((mI * tmp3));
	res3.y = ((mM * tmp2));
	res3.z = ((mA * tmp3));
	res3.w = ((mE * tmp2));
	res2.x = ((mI * tmp5));
	res2.y = ((mM * tmp4));
	res2.z = ((mA * tmp5));
	res2.w = ((mE * tmp4));
	tmp0 = ((mI * mB) - (mA * mJ));
	tmp1 = ((mM * mF) - (mE * mN));
	tmp2 = ((mI * mD) - (mA * mL));
	tmp3 = ((mM * mH) - (mE * mP));
	tmp4 = ((mI * mC) - (mA * mK));
	tmp5 = ((mM * mG) - (mE * mO));
	res2.x = ((((mL * tmp1) - (mJ * tmp3)) + res2.x));
	res2.y = ((((mP * tmp0) - (mN * tmp2)) + res2.y));
	res2.z = ((((mB * tmp3) - (mD * tmp1)) - res2.z));
	res2.w = ((((mF * tmp2) - (mH * tmp0)) - res2.w));
	res3.x = ((((mJ * tmp5) - (mK * tmp1)) + res3.x));
	res3.y = ((((mN * tmp4) - (mO * tmp0)) + res3.y));
	res3.z = ((((mC * tmp1) - (mB * tmp5)) - res3.z));
	res3.w = ((((mG * tmp0) - (mF * tmp4)) - res3.w));
	res1.x = ((((mK * tmp3) - (mL * tmp5)) - res1.x));
	res1.y = ((((mO * tmp2) - (mP * tmp4)) - res1.y));
	res1.z = ((((mD * tmp5) - (mC * tmp3)) + res1.z));
	res1.w = ((((mH * tmp4) - (mG * tmp2)) + res1.w));
	return Matrix4x4((res0 * detInv), (res1 * detInv), (res2 * detInv), (res3 * detInv));
}

Matrix4x4 Matrix4x4::OrthoInverse() const
{
	Vector3 inv0, inv1, inv2, inv3;
	inv0 = Vector3(mat[0][0], mat[1][0], mat[2][0]);
	inv1 = Vector3(mat[0][1], mat[1][1], mat[2][1]);
	inv2 = Vector3(mat[0][2], mat[1][2], mat[2][2]);

	Vector4 v1 = inv0 * mat[3][0];
	Vector4 v2 = inv1 * mat[3][1];
	Vector4 v3 = inv2 * mat[3][2];

	Vector4 col3 = Vector4((-((inv0 * mat[3][0]) + ((inv1 * mat[3][1]) + ((inv2 * mat[3][2]))))), 1.0f);

	return Matrix4x4(inv0, inv1, inv2, col3);
}

const float* Matrix4x4::GetData() const
{
	const float* data = reinterpret_cast<const float*>(mat);
	return data;
}