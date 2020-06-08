#pragma once

// CriticalSections are simpler and generally faster than Mutexes.
// If you don't need the signalling functionaliy of a Mutex, use a CriticalSection instead
class CriticalSection
{
public:
	CriticalSection() { ::InitializeCriticalSection(&m_lock); }
	~CriticalSection() { ::DeleteCriticalSection(&m_lock); }
	void EnterCriticalSection() { ::EnterCriticalSection(&m_lock); }
	void LeaveCriticalSection() { ::LeaveCriticalSection(&m_lock); }

private:
#if PLATFORM_WIN_ANY
	CRITICAL_SECTION m_lock;
#else
#error Figure out how to implement Critical Section on this platform
#endif
};
