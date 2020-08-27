#pragma once

// 4x4 Matrix class
struct Matrix
{
public:
	static const Matrix Identity;

public:
	struct F4x4
	{
		F4x4() {}
		F4x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33):
			_00(v00), _01(v01), _02(v02), _03(v03),
			_10(v10), _11(v11), _12(v12), _13(v13),
			_20(v20), _21(v21), _22(v22), _23(v23),
			_30(v30), _31(v31), _32(v32), _33(v33)
		{}

		float _00 = 0.0f, _01 = 0.0f, _02 = 0.0f, _03 = 0.0f;
		float _10 = 0.0f, _11 = 0.0f, _12 = 0.0f, _13 = 0.0f;
		float _20 = 0.0f, _21 = 0.0f, _22 = 0.0f, _23 = 0.0f;
		float _30 = 0.0f, _31 = 0.0f, _32 = 0.0f, _33 = 0.0f;
	};
	// Note: This is a similar setup to the D3DMatrix structure
	union
	{
		F4x4 a;
		float m[16];
	};

public:
	// Default constructor doesn't do any initialization
	Matrix() {}
	Matrix(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) :
		a(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33)
	{}
	Matrix(const Matrix& other);

	void Set(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
	{
		a._00 = v00;		a._01 = v01;		a._02 = v02;		a._03 = v03;
		a._10 = v10;		a._11 = v11;		a._12 = v12;		a._13 = v13;
		a._20 = v20;		a._21 = v21;		a._22 = v22;		a._23 = v23;
		a._30 = v30;		a._31 = v31;		a._32 = v32;		a._33 = v33;
	}

	// Set all elements to '0'
	void MakeZero();
	// Set equal to the identity
	void MakeIdentity();

	bool operator == (const Matrix& other) const;
	Matrix operator * (const Matrix& other) const;
	Vector4 operator * (const Vector4& vec) const;
};
