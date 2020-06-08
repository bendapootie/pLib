inline Timer::Timer()
{
	LARGE_INTEGER perf_freq;
	QueryPerformanceFrequency(&perf_freq);
	double perfFreqInverse = 1.0 / (double)perf_freq.QuadPart;
	m_scaleFreq = perfFreqInverse;

	// Timers are started on creation
	// Note: This initializes m_timerStopped, m_elapsedTime and m_lastQueryTime
	Start();
	m_timerStopped = false;
	m_elapsedTime = 0;
	QueryPerformanceCounter(&m_lastQueryTime);
}

// Reset and start the timer
inline void Timer::Start()
{
	m_timerStopped = false;
	m_elapsedTime = 0;
	QueryPerformanceCounter(&m_lastQueryTime);
}

// Stop the timer
inline void Timer::Stop()
{
	UpdateElapsedTime();
	m_timerStopped = true;
}

inline double Timer::GetTime()
{
	UpdateElapsedTime();
	// Note: There is a load-hit-store here for converting int-to-double
	return (double)m_elapsedTime * m_scaleFreq;
}

// TODO: Should this be inlined?
inline void Timer::UpdateElapsedTime()
{
	if (!m_timerStopped)
	{
		LARGE_INTEGER newTime;
		QueryPerformanceCounter(&newTime);
		m_elapsedTime += (newTime.QuadPart - m_lastQueryTime.QuadPart);
		m_lastQueryTime.QuadPart = newTime.QuadPart;
	}
}
