#pragma once

// 4x4 Matrix class
struct Matrix
{
public:
	static const Matrix Identity;

public:
	// Note: This is a similar setup to the D3DMatrix structure
	union
	{
		struct
		{
			float _00, _01, _02, _03;
			float _10, _11, _12, _13;
			float _20, _21, _22, _23;
			float _30, _31, _32, _33;
		};
		float m[16];
	};

public:
	// Default constructor doesn't do any initialization
	Matrix() {}
	Matrix(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) :
		_00(v00), _01(v01), _02(v02), _03(v03), _10(v10), _11(v11), _12(v12), _13(v13), _20(v20), _21(v21), _22(v22), _23(v23), _30(v30), _31(v31), _32(v32), _33(v33) {}
	Matrix(const Matrix& other);

	void Set(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
	{
		_00 = v00;		_01 = v01;		_02 = v02;		_03 = v03;
		_10 = v10;		_11 = v11;		_12 = v12;		_13 = v13;
		_20 = v20;		_21 = v21;		_22 = v22;		_23 = v23;
		_30 = v30;		_31 = v31;		_32 = v32;		_33 = v33;
	}

	// Set all elements to '0'
	void MakeZero();
	// Set equal to the identity
	void MakeIdentity();

	bool operator == (const Matrix& other) const;
	Matrix operator * (const Matrix& other) const;
	Vector4 operator * (const Vector4& vec) const;
};
