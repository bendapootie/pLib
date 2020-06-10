#pragma once


#if defined UNICODE
typedef wchar_t MutexChar;
#else
typedef char MutexChar;
#endif

// Mutex class for handling more complex locking needs than a CriticalSection can provide.
// CriticalSections are much faster than Mutexes and should be preferred when appropriate.
class Mutex
{
public:
	Mutex(const MutexChar* mutexId);
	~Mutex();
	void Lock();
	void Unlock();

private:
#if PLATFORM_WIN_ANY
	HANDLE m_mutexHandle;
#else
#error Figure out how to implement a Signaling Mutex on this platform
#endif
};

#include "Mutex.inl"