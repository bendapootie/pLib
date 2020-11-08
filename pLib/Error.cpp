#include "Precompiled.h"

#include <tchar.h>	// For OutputDebugString
#include <wchar.h>

namespace pLib
{
	static void AssertArgs(bool condition, const char* message, va_list args);
	static void ErrorArgs(const char* message, va_list args);

	static pList<ErrorHandler> ErrorHandlers;
	void PushErrorHandler(ErrorHandler newHandler)
	{
		ErrorHandlers.Add(newHandler);
	}

	void PopErrorHandler()
	{
		const int lastIndex = ErrorHandlers.Count() - 1;
		ErrorHandlers.RemoveAt(lastIndex);
	}

	static void HandleError(ErrorLevel errorLevel, const TCHAR* message, va_list args)
	{
		// TODO: Get rid of hard coded size (use snprintf to compute size?)
		constexpr int kStaticBufferSize = 1024;
		static TCHAR szBuffer[kStaticBufferSize];
		// Note: If (nBuf < 0) the buffer wasn't big enough
		const int nBuf = _vsnprintf_s(szBuffer, sizeof(szBuffer), _TRUNCATE, message, args);

		// Code that automatically appends line breaks to messages
		// TODO: Figure out if and when this behavior is appropriate
		bool kAppendLineBreak = true;
		if (kAppendLineBreak)
		{
			// Compute index to insert line break and null terminator
			int i = (nBuf >= 0) ? nBuf : kStaticBufferSize;
			i = Math::Min(i, kStaticBufferSize - 2);
			szBuffer[i] = '\n';
			szBuffer[i + 1] = '\0';
		}

		if (ErrorHandlers.Count() > 0)
		{
			auto errorHandler = ErrorHandlers[ErrorHandlers.Count() - 1];
			errorHandler(errorLevel, szBuffer);
		}
		else
		{
			switch (errorLevel)
			{
			case pLib::ErrorLevel::Notice:
				OutputDebugString(szBuffer);
				break;
			case pLib::ErrorLevel::Warning:
				OutputDebugString(szBuffer);
				break;
			case pLib::ErrorLevel::Error:
				OutputDebugString(szBuffer);
				break;
			case pLib::ErrorLevel::Fatal:
				OutputDebugString(szBuffer);
				break;
			}
		}
	}

	void Assert(bool condition, const char* message, ...)
	{
		if (condition == false)
		{
			va_list args;
			va_start(args, message);
			HandleError(ErrorLevel::Error, message, args);
			va_end(args);
		}
	}

	void Error(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		HandleError(ErrorLevel::Error, message, args);
		va_end(args);
	}

	void Warning(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		HandleError(ErrorLevel::Warning, message, args);
		va_end(args);
	}

	bool Verify(bool condition, const char* message, ...)
	{
		if (condition == false)
		{
			va_list args;
			va_start(args, message);
			HandleError(ErrorLevel::Error, message, args);
			va_end(args);
		}
		return condition;
	}

	void Debug(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		HandleError(ErrorLevel::Notice, message, args);
		va_end(args);
	}
}
