#pragma once

// ThreadSignal class used for suspending a thread until another action signals it to wake.
// Useful for putting a consumer thread to sleep until a procuder has more to give.
class ThreadSignal
{
public:
	enum class ResetStyle
	{
		Manual,
		Automatic
	};
public:
	ThreadSignal();
	~ThreadSignal();
	void Initialize(const MutexChar* threadSignalName, ResetStyle resetStyle, bool initialState);
	void WaitForSignal(uint32 milliseconds = 0xFFFFFFFF);
	void SetSignal();
	void ClearSignal();

private:
#if PLATFORM_WIN_ANY
	HANDLE m_signalHandle;
#else
#error Figure out how to implement a ThreadSignal on this platform
#endif
};

#include "ThreadSignal.inl"
