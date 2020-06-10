
inline Mutex::Mutex(const MutexChar* mutexId)
{
	m_mutexHandle = CreateMutex(nullptr, false, mutexId);
	pLib::Assert(m_mutexHandle != nullptr);
}

inline Mutex::~Mutex()
{
	if (m_mutexHandle != nullptr)
	{
		CloseHandle(m_mutexHandle);
		m_mutexHandle = nullptr;
	}
}

inline void Mutex::Lock()
{
	pLib::Assert(m_mutexHandle != nullptr);
	DWORD res = WaitForSingleObject(m_mutexHandle, INFINITE);
	pLib::Assert(res != WAIT_FAILED);
}

inline void Mutex::Unlock()
{
	DWORD res = ReleaseMutex(m_mutexHandle);
	pLib::Assert(res != 0); // zero = failure
}
