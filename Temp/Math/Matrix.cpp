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
	r._00 = (_00 * rhs._00) + (_01 * rhs._10) + (_02 * rhs._20) + (_03 * rhs._30);
	r._01 = (_00 * rhs._01) + (_01 * rhs._11) + (_02 * rhs._21) + (_03 * rhs._31);
	r._02 = (_00 * rhs._02) + (_01 * rhs._12) + (_02 * rhs._22) + (_03 * rhs._32);
	r._03 = (_00 * rhs._03) + (_01 * rhs._13) + (_02 * rhs._23) + (_03 * rhs._33);
	r._10 = (_10 * rhs._00) + (_11 * rhs._10) + (_12 * rhs._20) + (_13 * rhs._30);
	r._11 = (_10 * rhs._01) + (_11 * rhs._11) + (_12 * rhs._21) + (_13 * rhs._31);
	r._12 = (_10 * rhs._02) + (_11 * rhs._12) + (_12 * rhs._22) + (_13 * rhs._32);
	r._13 = (_10 * rhs._03) + (_11 * rhs._13) + (_12 * rhs._23) + (_13 * rhs._33);
	r._20 = (_20 * rhs._00) + (_21 * rhs._10) + (_22 * rhs._20) + (_23 * rhs._30);
	r._21 = (_20 * rhs._01) + (_21 * rhs._11) + (_22 * rhs._21) + (_23 * rhs._31);
	r._22 = (_20 * rhs._02) + (_21 * rhs._12) + (_22 * rhs._22) + (_23 * rhs._32);
	r._23 = (_20 * rhs._03) + (_21 * rhs._13) + (_22 * rhs._23) + (_23 * rhs._33);
	r._30 = (_30 * rhs._00) + (_31 * rhs._10) + (_32 * rhs._20) + (_33 * rhs._30);
	r._31 = (_30 * rhs._01) + (_31 * rhs._11) + (_32 * rhs._21) + (_33 * rhs._31);
	r._32 = (_30 * rhs._02) + (_31 * rhs._12) + (_32 * rhs._22) + (_33 * rhs._32);
	r._33 = (_30 * rhs._03) + (_31 * rhs._13) + (_32 * rhs._23) + (_33 * rhs._33);
	return r;
}

Vector4 Matrix::operator * (const Vector4& vec) const
{
	Vector4 result;
	result.x = (vec.x * _00) + (vec.y * _01) + (vec.z * _02) + (vec.w * _03);
	result.y = (vec.x * _10) + (vec.y * _11) + (vec.z * _12) + (vec.w * _13);
	result.z = (vec.x * _20) + (vec.y * _21) + (vec.z * _22) + (vec.w * _23);
	result.w = (vec.x * _30) + (vec.y * _31) + (vec.z * _32) + (vec.w * _33);
	return result;
}
