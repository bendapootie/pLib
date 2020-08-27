#include "Precompiled.h"

const Matrix Matrix::Identity(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);


Matrix::Matrix(const Matrix& rhs)
{
	// Todo: Is there a faster way to do this with SSE or just simple direct assignments?
	memcpy(this, &rhs, sizeof(Matrix));
}

void Matrix::MakeZero()
{
	// Set all elements to '0'
	memset(m, 0, sizeof(m));
}

void Matrix::MakeIdentity()
{
	// Set equal to the identity
	(*this) = Identity;
}

bool Matrix::operator == (const Matrix& other) const
{
	// Todo: Do this faster
	return (memcmp(&m, &other.m, sizeof(m)) == 0);
}

Matrix Matrix::operator * (const Matrix& rhs) const
{
	// Todo: Do this faster.  Use intrinsics, vector operations, library functions, etc...
	Matrix r;
	r.a._00 = (a._00 * rhs.a._00) + (a._01 * rhs.a._10) + (a._02 * rhs.a._20) + (a._03 * rhs.a._30);
	r.a._01 = (a._00 * rhs.a._01) + (a._01 * rhs.a._11) + (a._02 * rhs.a._21) + (a._03 * rhs.a._31);
	r.a._02 = (a._00 * rhs.a._02) + (a._01 * rhs.a._12) + (a._02 * rhs.a._22) + (a._03 * rhs.a._32);
	r.a._03 = (a._00 * rhs.a._03) + (a._01 * rhs.a._13) + (a._02 * rhs.a._23) + (a._03 * rhs.a._33);
	r.a._10 = (a._10 * rhs.a._00) + (a._11 * rhs.a._10) + (a._12 * rhs.a._20) + (a._13 * rhs.a._30);
	r.a._11 = (a._10 * rhs.a._01) + (a._11 * rhs.a._11) + (a._12 * rhs.a._21) + (a._13 * rhs.a._31);
	r.a._12 = (a._10 * rhs.a._02) + (a._11 * rhs.a._12) + (a._12 * rhs.a._22) + (a._13 * rhs.a._32);
	r.a._13 = (a._10 * rhs.a._03) + (a._11 * rhs.a._13) + (a._12 * rhs.a._23) + (a._13 * rhs.a._33);
	r.a._20 = (a._20 * rhs.a._00) + (a._21 * rhs.a._10) + (a._22 * rhs.a._20) + (a._23 * rhs.a._30);
	r.a._21 = (a._20 * rhs.a._01) + (a._21 * rhs.a._11) + (a._22 * rhs.a._21) + (a._23 * rhs.a._31);
	r.a._22 = (a._20 * rhs.a._02) + (a._21 * rhs.a._12) + (a._22 * rhs.a._22) + (a._23 * rhs.a._32);
	r.a._23 = (a._20 * rhs.a._03) + (a._21 * rhs.a._13) + (a._22 * rhs.a._23) + (a._23 * rhs.a._33);
	r.a._30 = (a._30 * rhs.a._00) + (a._31 * rhs.a._10) + (a._32 * rhs.a._20) + (a._33 * rhs.a._30);
	r.a._31 = (a._30 * rhs.a._01) + (a._31 * rhs.a._11) + (a._32 * rhs.a._21) + (a._33 * rhs.a._31);
	r.a._32 = (a._30 * rhs.a._02) + (a._31 * rhs.a._12) + (a._32 * rhs.a._22) + (a._33 * rhs.a._32);
	r.a._33 = (a._30 * rhs.a._03) + (a._31 * rhs.a._13) + (a._32 * rhs.a._23) + (a._33 * rhs.a._33);
	return r;
}

Vector4 Matrix::operator * (const Vector4& vec) const
{
	Vector4 result;
	result.x = (vec.x * a._00) + (vec.y * a._01) + (vec.z * a._02) + (vec.w * a._03);
	result.y = (vec.x * a._10) + (vec.y * a._11) + (vec.z * a._12) + (vec.w * a._13);
	result.z = (vec.x * a._20) + (vec.y * a._21) + (vec.z * a._22) + (vec.w * a._23);
	result.w = (vec.x * a._30) + (vec.y * a._31) + (vec.z * a._32) + (vec.w * a._33);
	return result;
}
