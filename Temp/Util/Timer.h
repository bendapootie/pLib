#pragma once

//--------------------------------------------------------------------------------------
// Helper class to perform timer operations
// Start()           - To start the timer
// Stop()            - To stop (or pause) the timer
// GetTime()         - Returns current time or last stopped time
//--------------------------------------------------------------------------------------
class Timer
{
public:
	Timer();

	// Reset and start the timer
	void Start();
	// Stop the timer
	void Stop();

	// Returns time elapsed in seconds.
	// If timer is stopped, returns the elapsed time while it was running.
	// It timer is running, returns the current elapsed time.
	double GetTime();
	static_assert(sizeof(double) == 8, "If 'double' isn't a 64-bit floating point value, timing could get off after running for a while");

private:
	void UpdateElapsedTime();

private:
	LARGE_INTEGER m_lastQueryTime;
	LONGLONG m_elapsedTime; // delayed conversion to double to avoid load-hit-store
	double m_scaleFreq; // (timeScale / perfFreq); Needed to convert from QueryPerformanceFrequency to seconds

	bool m_timerStopped;
};


#include "Timer.inl"
