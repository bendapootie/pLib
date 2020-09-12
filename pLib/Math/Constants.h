#pragma once

namespace Math
{
	static_assert(sizeof(float) == 4, "Assuming that float is 4 bytes");
	static_assert(sizeof(double) == 8, "Assuming that double is 8 bytes");

	constexpr double Pi = 3.14159265358979323846264338327950;
	constexpr double PiOver2 = Pi / 2.0;
	constexpr float PiF = 3.14159265358979f;
	constexpr float PiOver2F = PiF / 2.0f;

	const int8 Int8Min = (-127) - 1;
	const int8 Int8Max = 127;
	const int16 Int16Min = (-32767) - 1;
	const int16 Int16Max = 32767;
	const int32 Int32Min = (-2147483647) - 1;
	const int32 Int32Max = 2147483647;
	const int64 Int64Min = (-9223372036854775807) - 1;
	const int64 Int64Max = 9223372036854775807;

	const uint8 UInt8Min = 0;
	const uint8 UInt8Max = 255;
	const uint16 UInt16Min = 0;
	const uint16 UInt16Max = 65535;
	const uint32 UInt32Min = 0;
	const uint32 UInt32Max = 4294967295;
	const uint64 UInt64Min = 0;
	const uint64 UInt64Max = 18446744073709551615;

	const float FloatEpsilon = 1.192092896e-07F;	// smallest value such that (1.0 + FloatEpsilon) != 1.0
	const float FloatMax = 3.402823466e+38F;		// max value
	const float FloatMin = 1.175494351e-38F;		// min positive value
	const float FloatSmallNumber = 0.000001f;		// "smallish" number, useful for epsilon tests

	const double DoubleEpsilon = 2.2204460492503131e-016;	// smallest value such that (1.0 + DoubleEpsilon) != 1.0
	const double DoubleMax = 1.7976931348623158e+308;		// max value
	const double DoubleMin = 2.2250738585072014e-308;		// min positive value
};
