#include "Precompiled.h"
#include <tchar.h>	// For OutputDebugString

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

	static void HandleError(ErrorLevel errorLevel, const char* message, va_list args)
	{
		int nBuf;
		static TCHAR szBuffer[1024];	// TODO: Get rid of hard coded size
		nBuf = _vsnprintf_s(szBuffer, sizeof(szBuffer)-1, message, args);

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
