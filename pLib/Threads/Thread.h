#pragma once

#if PLATFORM_WIN_ANY
typedef LPTHREAD_START_ROUTINE ThreadStartFunction;
typedef LPVOID ThreadParameter;
typedef DWORD ThreadReturnType;
#else
#error Unsupported platform
#endif

class Thread
{
public:
	Thread(const char* const entityName);
	virtual ~Thread();

	bool IsInitialized() const;
	virtual void Initialize(ThreadStartFunction startFunction, ThreadParameter parameter);

	// Returns 'true' if this thread is executing the caller's code.
	// Mostly used for debugging to ensure only certain functions are run by certain threads.
	bool IsCurrentThread();

	void Suspend();
	void Resume();

private:
	char* m_threadName;		// Used only for debugging
	HANDLE m_threadHandle;
	DWORD m_threadId;
	int m_suspendCount;
};
