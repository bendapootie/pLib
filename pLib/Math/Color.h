#pragma once

#include "Math.h"
#include "Vector.h"

//=============================================================================
// Helper struct that deals with four individual components
struct Color4x8
{
public:
	Color4x8(const uint8 r, const uint8 g, const uint8 b, const uint8 a) :
		r_(r),
		g_(g),
		b_(b),
		a_(a)
	{
	}

public:
	// Note: The order of these is important for aligning with the uint32 representation
	//       This order may need to be flipped on a big-endian machine
	uint8 a_ = 255;
	uint8 b_ = 0;
	uint8 g_ = 0;
	uint8 r_ = 0;
};

//=============================================================================
// Represents a 32-bit RGBA color value
// 
// Conversions to/from float values are a little different from the standard multiply/divide by 255
// Dividing by 255 is nice for mapping the minimum integer value to the minimum float value, but
// it means that the float ranges covered by each color aren't all the same size.
//
// The following conversions map the integer values to the center of the float range
// And the float ranges are all equal size
//
// int = Floor(float * 256.0f)
// float = (int + 0.5f) / 256.0f
struct Color32
{
public:
	union
	{
		uint32 rgba_ = 0;
		Color4x8 c_;
	};

public:
	// Default constructor doesn't do any extra initialization
	Color32() {}
	Color32(uint32 uint32_color) : rgba_(uint32_color) {}
	Color32(const uint8 r, const uint8 g, const uint8 b, const uint8 a = 255) :
		c_(r, g, b, a)
	{}
	Color32(const Vector4& vector_color) :
		Color32(
			static_cast<uint8>(Math::Clamp(vector_color.x * 256.0f, 0.0f, 255.0f)),
			static_cast<uint8>(Math::Clamp(vector_color.y * 256.0f, 0.0f, 255.0f)),
			static_cast<uint8>(Math::Clamp(vector_color.z * 256.0f, 0.0f, 255.0f)),
			static_cast<uint8>(Math::Clamp(vector_color.w * 256.0f, 0.0f, 255.0f))
			)
	{
	}

	static Color32 FromFloats(const float r, const float g, const float b, const float a = 1.0f)
	{
		return Color32(Vector4(r, g, b, a));
	}

	Vector4 ToVector4() const
	{
		return Vector4(c_.r_ + 0.5f, c_.g_ + 0.5f, c_.b_ + 0.5f, c_.a_ + 0.5f) * (1.0f / 256.0f);
	}

	uint32 ToUint32() const
	{
		return rgba_;
	}
};

//=============================================================================
