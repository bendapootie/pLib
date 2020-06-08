inline ThreadSignal::ThreadSignal() :
	m_signalHandle(nullptr)
{
}

inline ThreadSignal::~ThreadSignal()
{
	if (m_signalHandle != nullptr)
	{
		CloseHandle(m_signalHandle);
		m_signalHandle = nullptr;
	}
}

inline void ThreadSignal::Initialize(const char* threadSignalName, ResetStyle resetStyle, bool initialState)
{
	pLib::Assert(m_signalHandle == nullptr, "Initialize should only be called on an empty object");
	const bool manualReset = (resetStyle == ResetStyle::Manual);
	m_signalHandle = CreateEvent(nullptr, manualReset, initialState, threadSignalName);
	pLib::Assert(m_signalHandle != nullptr);
}

// Puts the current thread to sleep for the given number of milliseconds (default is INFINITY)
// or until the signal is set.
// Note: If the signal has not been cleared when this function is called, it won't sleep.
inline void ThreadSignal::WaitForSignal(uint32 milliseconds)
{
	pLib::Assert(m_signalHandle != nullptr);
	DWORD res = WaitForSingleObject(m_signalHandle, milliseconds);
	pLib::Assert(res != WAIT_FAILED);
}

inline void ThreadSignal::SetSignal()
{
	// Seting the event will wake the sleeping thread
	DWORD res = SetEvent(m_signalHandle);
	pLib::Assert(res != 0); // zero == failure
}

inline void ThreadSignal::ClearSignal()
{
	DWORD res = ResetEvent(m_signalHandle);
	pLib::Assert(res != 0); // zero == failure
}
