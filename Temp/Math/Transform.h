#pragma once

// A 3d Transform that consists of the following...
// - Position as a Vector3
// - Rotation as a Quaternion
// - Scale as (x,y,z) in a Vector3
class Transform
{
public:
	static const Transform Identity;

public:
	// TODO: Should we use Vector4s for Position and Scale for padding reasons?  16 byte vectors are nicer than 12 byte ones for lots of reasons.
	Quaternion Rotation;
	Vector3 Position;
	Vector3 Scale;

public:
	// Empty constructor doesn't initialize anything
	Transform() {}
	Transform(const Transform& other) : Rotation(other.Rotation), Position(other.Position), Scale(other.Scale) {}
	Transform(const Vector3 position, const Quaternion rotation, const Vector3 scale) : Rotation(rotation), Position(position), Scale(scale) {}

	bool operator == (const Transform& other) const { return (Rotation == other.Rotation) && (Position == other.Position) && (Scale == other.Scale); }
	bool operator != (const Transform& other) const { return !(operator==(other)); }

	Transform operator * (const Transform& other) const;
	void operator *= (const Transform& other);
	// Dividing by a transform is the same as multiplying by its inverse
	Transform operator / (const Transform& other) const;
	void operator /= (const Transform& other);

	Vector3 ApplyTransform(const Vector3& input) const;

	// Returns the transform in a 4x4 Matrix
	Matrix ToMatrix() const;
};
