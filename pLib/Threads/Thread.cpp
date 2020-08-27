#include "Precompiled.h"

const DWORD ThreadIdNone = 0;

Thread::Thread(const char* const threadName) :
	m_threadName(""),
	m_threadHandle(nullptr),
	m_threadId(ThreadIdNone),
	m_suspendCount(0)
{
	// Todo: Track names in a better way.  Maybe in a dynamic string cache than just randomly in the heap?
	int size = (int)(strlen(threadName) + 1);
	m_threadName = new char[size];
	strcpy_s(m_threadName, size, threadName);
}

Thread::~Thread()
{
}

bool Thread::IsInitialized() const
{
	return (m_threadHandle != nullptr) && (m_threadId != ThreadIdNone);
}

void Thread::Initialize(ThreadStartFunction startFunction, ThreadParameter parameter)
{
	if (IsInitialized())
	{
		pLib::Error("Can't initialize a Thread that's already initialized");
		return;
	}

	LPSECURITY_ATTRIBUTES lpThreadAttributes = nullptr;
	SIZE_T stackSize = 0;		// 0 = Use default stack size
	DWORD dwCreationFlags = CREATE_SUSPENDED;	// All threads start suspended

	m_threadHandle = CreateThread(
		lpThreadAttributes,
		stackSize,
		startFunction,		// LPTHREAD_START_ROUTINE
		parameter,			// LPVOID
		dwCreationFlags,	// DWORD
		&m_threadId);		// LPDWORD

	// All threads created with CREATE_SUSPENDED start with a suspend count
	// of 1 and need to be Resumed() before they will start execution.
	m_suspendCount = 1;
}

bool Thread::IsCurrentThread()
{
	bool isCurrentThread = (GetCurrentThreadId() == m_threadId);
	return isCurrentThread;
}

void Thread::Suspend()
{
	DWORD oldSuspendCount = SuspendThread(m_threadHandle);
	pLib::Assert(m_suspendCount == (int)oldSuspendCount, "Make sure suspend counts match");
	m_suspendCount++;
}

void Thread::Resume()
{
	DWORD oldSuspendCount = ResumeThread(m_threadHandle);
	pLib::Assert(m_suspendCount == (int)oldSuspendCount, "Make sure suspend counts match");
	m_suspendCount--;
}
