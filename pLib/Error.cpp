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
		static TCHAR szBuffer[1024];	// TODO: Get rid of hard coded size (use snprintf to compute size?)
		const int nBuf = _vsnprintf_s(szBuffer, sizeof(szBuffer), _TRUNCATE, message, args);
		// if (nBuf < -1) the buffer wasn't big enough

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
