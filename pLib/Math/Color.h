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
			static_cast<uint8>(Math::Round(Math::Clamp(vector_color.x * 255.0f, 0.0f, 255.0f))),
			static_cast<uint8>(Math::Round(Math::Clamp(vector_color.y * 255.0f, 0.0f, 255.0f))),
			static_cast<uint8>(Math::Round(Math::Clamp(vector_color.z * 255.0f, 0.0f, 255.0f))),
			static_cast<uint8>(Math::Round(Math::Clamp(vector_color.w * 255.0f, 0.0f, 255.0f)))
			)
	{
	}

	static Color32 FromFloats(const float r, const float g, const float b, const float a = 1.0f)
	{
		return Color32(Vector4(r, g, b, a));
	}

	Vector4 ToVector4() const
	{
		// TODO: Consider using different conversion functions that rely on '256' instead of '255'
		//       Issue #51 - https://github.com/bendapootie/GridGame/issues/51
		//       Argument here - http://eastfarthing.com/blog/2015-12-19-color/
		//       f32 = (uint8 + 0.5f) / 256.0f
		//       uint8 = (uint8)(f32 * 256.0f)
		return Vector4(c_.r_, c_.g_, c_.b_, c_.a_) * (1.0f / 255.0f);
	}

	uint32 ToUint32() const
	{
		return rgba_;
	}
};

//=============================================================================
