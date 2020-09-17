#pragma once

#include "Math.h"

struct Vector2;
struct Vector3;
struct Vector4;

// TODO: Make a template to support float and double vectors?
struct Vector2
{
public:
	static const Vector2 Zero;		// (0, 0)
	static const Vector2 One;		// (1, 1)
	static const Vector2 UnitX;		// (1, 0)
	static const Vector2 UnitY;		// (0, 1)

public:
	float x = 0.0f;
	float y = 0.0f;

	// Default constructor doesn't do any initialization
	Vector2() {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(const Vector2& other) : x(other.x), y(other.y) {}

	// Somewhat hacky functions to get a 'float' pointer to the start of the Vector
	const float* Ptr() const { return &x; }
	float* Ptr() { return &x; }

	Vector3 ToVector3(float z = 0.0f);

	bool operator == (const Vector2& other) const { return (x == other.x) && (y == other.y); }
	bool operator != (const Vector2& other) const { return !(operator==(other)); }

	bool Equals(const Vector2& other, const float tolerance = Math::FloatSmallNumber) const
	{
		return Math::Abs(x - other.x) <= tolerance && Math::Abs(y - other.y) <= tolerance;
	}

	float Dot(const Vector2& other) const { return (x * other.x) + (y * other.y); }

	// In-place vector math functions
	void Add(const Vector2& rhs);
	void Subtract(const Vector2& rhs);

	void NormalizeInPlace();
	Vector2 GetNormalized() const;

	// Versions of 'normalize' that return Zero if called on a zero length vector
	void SafeNormalizeInPlace();
	Vector2 GetSafeNormalized() const;

	float GetLength() const;
	float GetLengthSquared() const;

	float GetDistance(const Vector2& point) const;
	float GetDistanceSquared(const Vector2& point) const;

	// Other vector functions
	Vector2 PerElementMultiply(const Vector2& rhs) const;
	Vector2 PerElementDivide(const Vector2& rhs) const;

	// Vector overloaded operators
	Vector2 operator + (const Vector2& rhs) const;
	void operator += (const Vector2& rhs);
	Vector2 operator - (const Vector2& rhs) const;
	void operator -= (const Vector2& rhs);
	Vector2 operator * (const float scale) const { return Vector2(x * scale, y * scale); }
	void operator *= (const float scale) { x *= scale; y *= scale; }
	Vector2 operator / (const float scale) const { return Vector2(x / scale, y / scale); }
	void operator /= (const float scale) { x /= scale; y /= scale; }
};

struct Vector3
{
public:
	static const Vector3 Zero;		// (0, 0, 0)
	static const Vector3 One;		// (1, 1, 1)
	static const Vector3 UnitX;		// (1, 0, 0)
	static const Vector3 UnitY;		// (0, 1, 0)
	static const Vector3 UnitZ;		// (0, 0, 1)

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	// Default constructor doesn't do any initialization
	Vector3() {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

	// Somewhat hacky functions to get a 'float' pointer to the start of the Vector
	const float* Ptr() const { return &x; }
	float* Ptr() { return &x; }

	bool operator == (const Vector3& other) const { return (x == other.x) && (y == other.y) && (z == other.z); }
	bool operator != (const Vector3& other) const { return !(operator==(other)); }

	bool Equals(const Vector3& other, const float tolerance = Math::FloatSmallNumber) const
	{
		return Math::Abs(x - other.x) <= tolerance && Math::Abs(y - other.y) <= tolerance && Math::Abs(z - other.z) <= tolerance;
	}

	float Dot(const Vector3& other) const { return (x * other.x) + (y * other.y) + (z * other.z); }
	Vector3 Cross(const Vector3& other) const { return Vector3((y * other.z) - (other.y * z), (z * other.x) - (other.z * x), (x * other.y) - (other.x * y)); }

	// In-place vector math functions
	void Add(const Vector3& rhs);
	void Subtract(const Vector3& rhs);

	void NormalizeInPlace();
	Vector3 GetNormalized() const;

	float GetLength() const;
	float GetLengthSquared() const;
	float GetDistance(const Vector3& point) const;
	float GetDistanceSquared(const Vector3& point) const;

	// Other vector functions
	Vector3 PerElementMultiply(const Vector3& rhs) const;
	Vector3 PerElementDivide(const Vector3& rhs) const;

	void RotateAroundAxis(const Vector3& axis, const float angle);

	void RotateAroundXAxis(const float angle);
	void RotateAroundYAxis(const float angle);
	void RotateAroundZAxis(const float angle);
	void RotateYawPitchRoll(const float yaw, const float pitch, const float roll);

	// Vector overloaded operators
	Vector3 operator - () const;						// Unary negation operator
	Vector3 operator + (const Vector3& rhs) const;
	void operator += (const Vector3& rhs);
	Vector3 operator - (const Vector3& rhs) const;
	void operator -= (const Vector3& rhs);
	Vector3 operator * (const float scale) const { return Vector3(x * scale, y * scale, z * scale); }
	Vector3 operator / (const float d) const { return Vector3(x / d, y / d, z / d); }
	void operator *= (const float scale) { x *= scale; y *= scale; z *= scale; }

	// Static utility functions
	static Vector3 Lerp(const Vector3& start, const Vector3& end, const float t);
};

struct Vector4
{
public:
	static const Vector4 Zero;		// (0, 0, 0, 0)
	static const Vector4 One;		// (1, 1, 1, 1)
	static const Vector4 UnitX;		// (1, 0, 0, 0)
	static const Vector4 UnitY;		// (0, 1, 0, 0)
	static const Vector4 UnitZ;		// (0, 0, 1, 0)
	static const Vector4 UnitW;		// (0, 0, 0, 1)

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;	// Note: 'w' comes after x,y,z

	// Default constructor doesn't do any initialization
	Vector4() {}
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

	// Somewhat hacky functions to get a 'float' pointer to the start of the Vector
	const float* Ptr() const { return &x; }
	float* Ptr() { return &x; }

	// Conversions
	// Returns a copy of the Vector4 in Vector3 format, omitting the 'w' component
	Vector3 ToVector3() const { return Vector3(x, y, z); }
	// Returns a copy of the Vector4 in Quaternion format
	Quaternion ToQuaternion() const { return Quaternion(x, y, z, w); }
	// Returns a reference to this Vector4 in Vector3 format
	Vector3& AsVector3() { return *reinterpret_cast<Vector3*>(this); }
	const Vector3& AsVector3() const { return *reinterpret_cast<const Vector3*>(this); }
	// Returns a reference to this Vector4 in Quaternion format
	Quaternion& AsQuaternion() { return *reinterpret_cast<Quaternion*>(this); }
	const Quaternion& AsQuaternion() const { return *reinterpret_cast<const Quaternion*>(this); }

	bool operator == (const Vector4& other) const { return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w); }
	bool operator != (const Vector4& other) const { return !(operator==(other)); }

	bool Equals(const Vector4& other, const float tolerance = Math::FloatSmallNumber) const
	{
		return Math::Abs(x - other.x) <= tolerance && Math::Abs(y - other.y) <= tolerance && Math::Abs(z - other.z) <= tolerance && Math::Abs(w - other.w) <= tolerance;
	}

	float Dot(const Vector4& other) const { return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }

	// In-place vector math functions
	void Add(const Vector4& rhs);
	void Subtract(const Vector4& rhs);

	void NormalizeInPlace();
	Vector4 GetNormalized() const;

	// Other vector functions
	Vector4 PerElementMultiply(const Vector4& rhs) const;
	Vector4 PerElementDivide(const Vector4& rhs) const;

	// Vector overloaded operators
	Vector4 operator + (const Vector4& rhs) const;
	void operator += (const Vector4 &rhs);
	Vector4 operator - (const Vector4& rhs) const;
	void operator -= (const Vector4 &rhs);
	Vector4 operator * (const float scale) const { return Vector4(x * scale, y * scale, z * scale, w * scale); }
	void operator *= (const float scale) { x *= scale; y *= scale; z *= scale; w *= scale; }
	Vector4 operator / (const float scale) const { return Vector4(x / scale, y / scale, z / scale, w / scale); }
	void operator /= (const float scale) { x /= scale; y /= scale; z /= scale; w /= scale; }
};


//-----------------------------------------------------------------------------
// Vector2 - Inline implementation
//-----------------------------------------------------------------------------
inline Vector3 Vector2::ToVector3(float z)
{
	return Vector3(x, y, z);
}
