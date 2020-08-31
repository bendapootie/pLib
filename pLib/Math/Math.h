#pragma once

namespace Math
{
	inline float Abs(float f) { return ::fabsf(f); }
	inline double Abs(double d) { return ::fabs(d); }
	inline int8 Abs(int8 n) { return (int8)::abs(n); }
	inline int16 Abs(int16 n) { return (int16)::abs(n); }
	inline int32 Abs(int32 n) { return ::abs(n); }
	inline int64 Abs(int64 n) { return (n >= 0) ? n : -n; }		// Compiler barks if int64 tries to call ::abs()

	template <class T> const T& Min (const T& a, const T& b) { return (a < b) ? a : b; }
	template <class T> const T& Max (const T& a, const T& b) { return !(a < b) ? a : b; }

	template <class T> const T Clamp(const T& v, const T& a, const T& b) { return Max(a, Min(b, v)); }
	template <class T> const T Lerp(const T& a, const T& b, const T& t) { return a + (t * (b - a)); }

	inline float Ceil(float f) { return ::ceilf(f); }
	inline float Floor(float f) { return ::floorf(f); }
	inline float Round(float f) { return ::roundf(f); }

	// Trig functions
	inline float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }
	inline float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	inline float Sin(float f) { return ::sinf(f); }
	inline float Cos(float f) { return ::cosf(f); }
	inline float Tan(float f) { return ::tanf(f); }
	inline float ASin(float f) { return ::asinf(f); }
	inline float ACos(float f) { return ::acosf(f); }
	inline float ATan(float f) { return ::atanf(f); }
	inline float ATan2(float y, float x) { return ::atan2f(y, x); }
	inline void SinCos(float f, float& s, float& c) { s = Sin(f); c = Cos(f); }
	inline float Sqr(float f) { return f * f; }
	inline float Sqrt(float f) { return ::sqrtf(f); }
	inline float InvSqrt(float f) { return 1.0f / ::sqrtf(f); }
	inline float Power(float base, float exponent) { return ::powf(base, exponent); }

	inline double Sin(double d) { return ::sin(d); }
	inline double Cos(double d) { return ::cos(d); }
	inline double Tan(double d) { return ::tan(d); }
	inline double ASin(double d) { return ::asin(d); }
	inline double ACos(double d) { return ::acos(d); }
	inline double ATan(double d) { return ::atan(d); }
	inline double ATan2(double y, double x) { return ::atan2(y, x); }
	inline void SinCos(double d, double& s, double& c) { s = Sin(d); c = Cos(d); }
	inline double Sqr(double d) { return d * d; }
	inline double Sqrt(double d) { return ::sqrt(d); }
	inline double InvSqrt(double d) { return 1.0 / ::sqrt(d); }
	inline double Power(double base, double exponent) { return ::pow(base, exponent); }
};
