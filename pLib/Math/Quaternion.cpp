#include "Precompiled.h"

//
// Good quaternion implementation reference here...
// http://willperone.net/Code/quaternion.php
//

const Quaternion Quaternion::Identity(0, 0, 0, 1);

Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

void Quaternion::MakeConjugate()
{
	x = -x;
	y = -y;
	z = -z;
}

Quaternion Quaternion::operator * (const Quaternion& other) const
{
	const float dotResult = this->AsVector3().Dot(other.AsVector3());
	return Quaternion(
		y * other.z - z * other.y + w * other.x + x * other.w,
		z * other.x - x * other.z + w * other.y + y * other.w,
		x * other.y - y * other.x + w * other.z + z * other.w,
		w * other.w - dotResult);
}

void Quaternion::FrowEulerAngles(float in_z, float in_y, float in_x)
{
	float sinX2, cosX2;
	float sinY2, cosY2;
	float sinZ2, cosZ2;

	Math::SinCos(0.5f * in_x, sinX2, cosX2);
	Math::SinCos(0.5f * in_y, sinY2, cosY2);
	Math::SinCos(0.5f * in_z, sinZ2, cosZ2);

	// and now compute quaternion
	x = (cosZ2 * cosY2 * sinX2) - (sinZ2 * sinY2 * cosX2);
	y = (cosZ2 * sinY2 * cosX2) + (sinZ2 * cosY2 * sinX2);
	z = (sinZ2 * cosY2 * cosX2) - (cosZ2 * sinY2 * sinX2);
	w = (cosZ2 * cosY2 * cosX2) + (sinZ2 * sinY2 * sinX2);
}

// Todo: Figure out how to get around Vector conversion functions to be inlined
inline Vector4 Quaternion::ToVector4() const
{
	return Vector4(x, y, z, w);
}

inline Vector4& Quaternion::AsVector4()
{
	return *reinterpret_cast<Vector4*>(this);
}

inline const Vector4& Quaternion::AsVector4() const
{
	return *reinterpret_cast<const Vector4*>(this);
}

inline Vector3 Quaternion::ToVector3() const
{
	return Vector3(x, y, z);
}

inline Vector3& Quaternion::AsVector3()
{
	return *reinterpret_cast<Vector3*>(this);
}

inline const Vector3& Quaternion::AsVector3() const
{
	return *reinterpret_cast<const Vector3*>(this);
}

Vector3 Quaternion::RotateVector(const Vector3& input) const
{
	Quaternion v(input.x, input.y, input.z, 0);
	Quaternion conjugate = GetConjugate();
	return (*this * v * conjugate).ToVector3();
}

Matrix Quaternion::GetMatrix() const
{
	Matrix m(Matrix::Identity);
	const float ww = w * w;
	const float xx = x * x;
	const float yy = y * y;
	const float zz = z * z;

	pLib::Assert(Math::Abs(xx + yy + zz + ww) > Math::FloatEpsilon, "Don't divide by zero!");

	// Todo: For perf reasons, can we assume all quaternions are normalized?
	// invs (inverse square length) is only required if quaternion is not already normalised
	const float invs = 1.0f / (xx + yy + zz + ww);
	m.a._00 = (xx - yy - zz + ww) * invs; // since ww + xx + yy + zz = 1 / invs * invs
	m.a._11 = (-xx + yy - zz + ww) * invs;
	m.a._22 = (-xx - yy + zz + ww) * invs;

	const float xy = x * y;
	const float zw = z * w;
	m.a._10 = 2.0f * (xy + zw) * invs;
	m.a._01 = 2.0f * (xy - zw) * invs;

	const float xz = x * z;
	const float yw = y * w;
	m.a._20 = 2.0f * (xz - yw) * invs;
	m.a._02 = 2.0f * (xz + yw) * invs;

	const float yz = y * z;
	const float xw = x * w;
	m.a._21 = 2.0f * (yz + xw) * invs;
	m.a._12 = 2.0f * (yz - xw) * invs;

	return m;
}

/*
//! returns the euler angles from a rotation quaternion
vector3f euler_angles(bool homogenous = true) const
{
	float sqw = s*s;
	float sqx = v.x*v.x;
	float sqy = v.y*v.y;
	float sqz = v.z*v.z;

	vector3f euler;
	if (homogenous) {
		euler.x = atan2f(2.f * (v.x*v.y + v.z*s), sqx - sqy - sqz + sqw);
		euler.y = asinf(-2.f * (v.x*v.z - v.y*s));
		euler.z = atan2f(2.f * (v.y*v.z + v.x*s), -sqx - sqy + sqz + sqw);
	}
	else {
		euler.x = atan2f(2.f * (v.z*v.y + v.x*s), 1 - 2 * (sqx + sqy));
		euler.y = asinf(-2.f * (v.x*v.z - v.y*s));
		euler.z = atan2f(2.f * (v.x*v.y + v.z*s), 1 - 2 * (sqy + sqz));
	}
	return euler;
}
*/