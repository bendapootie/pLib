#pragma once

static_assert(1 == 1, "Sanity check to make sure static_assert is defined");
// Possible 'static_assert' macro for compilers that don't have one
//#define static_assert( condition, name )\
//	typedef char assert_failed_ ## name[(condition) ? 1 : -1];

namespace pLib
{
	enum class ErrorLevel
	{
		Invalid = -1,

		Notice,
		Warning,
		Error,
		Fatal,

		Count
	};

	void Assert(bool condition, const char* message = "", ...);
	bool Verify(bool condition, const char* message = "", ...);
	void Error(const char* message = "", ...);
	void Warning(const char* message, ...);
	void Debug(const char* message, ...);

	typedef void(*ErrorHandler)(ErrorLevel errorLevel, const char* message);

	void PushErrorHandler(ErrorHandler newHandler);
	void PopErrorHandler();
}