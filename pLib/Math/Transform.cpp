#include "Precompiled.h"

const Transform Transform::Identity(
	Vector3(0.0f, 0.0f, 0.0f),			// position = (0, 0, 0)
	Quaternion(0.0f, 0.0f, 0.0f, 1.0f),		// rotation = (0, 0, 0, 1)
	Vector3(1.0f, 1.0f, 1.0f));			// scale = (1, 1, 1)

Transform Transform::operator * (const Transform& other) const
{
	// World = Parent * Local (*this == parent)
	Transform result;
	result.Position = Position + Rotation.RotateVector(other.Position.PerElementMultiply(Scale));
	result.Rotation = Rotation * other.Rotation;

	result.Scale = Scale.PerElementMultiply(other.Scale);
	// TODO: I used to have the following line, but I don't know why
	//result.Scale = Scale.PerElementMultiply(Rotation.RotateVector(other.Scale));

	return result;
}

void Transform::operator *= (const Transform& other)
{
	(*this) = (*this) * other;
}

// Dividing by a transform is the same as multiplying by its inverse
Transform Transform::operator / (const Transform& other) const
{
	pLib::Error("Todo: Implement");
	/*
	tTransform localSpace;
	tQuaternion parentSpaceConjugate = parentSpace.Rotation.conjugate();
	localSpace.Position = (parentSpaceConjugate * (Position - parentSpace.Position)) / parentSpace.Scale;

	localSpace.Rotation = parentSpaceConjugate * Rotation;

	localSpace.Scale = parentSpaceConjugate * (Scale / parentSpace.Scale);
	return localSpace;
	*/
	return other;
}

void Transform::operator /= (const Transform& other)
{
	(*this) = (*this) / other;
}

Vector3 Transform::ApplyTransform(const Vector3& input) const
{
	// Scale first, then rotate, and finally translate
	Vector3 result = Rotation.RotateVector(input.PerElementMultiply(Scale)) + Position;

	return result;
}

// Returns the transform in a 4x4 Matrix
Matrix Transform::ToMatrix() const
{
	// Transformations get applied from right to left.
	// output = [position * rotation * scale] * input
	// transform matrix = [position * rotation * scale]

	// Get rotation matrix from quaternion
	Matrix result = Rotation.GetMatrix();
	// Apply scale
	result._00 *= Scale.x;	result._01 *= Scale.y;	result._02 *= Scale.z;
	result._10 *= Scale.x;	result._11 *= Scale.y;	result._12 *= Scale.z;
	result._20 *= Scale.x;	result._21 *= Scale.y;	result._22 *= Scale.z;
	// Apply position
	result._03 = Position.x;
	result._13 = Position.y;
	result._23 = Position.z;

	return result;
}
