#pragma once

#include "sge_defines.h"


class StopWatch
{
public:
	StopWatch(bool AutoReset = true);
	~StopWatch() = default;

	f64 GetElapsedMilliseconds();
	f64 GetElapsedSeconds();
	void Reset();

private:
	void initialize();

private:
	LARGE_INTEGER m_Freq;
	LARGE_INTEGER m_LastTick;
	f64           m_InvFreq;
	f64           m_Accum;
	bool          m_AutoReset;

};
