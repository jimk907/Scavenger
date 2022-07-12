#include "time_utils.h"




StopWatch::StopWatch(bool AutoReset)
	: m_Freq({ 0 }), m_InvFreq(0.0)
	, m_LastTick({ 0 }), m_Accum(0.0)
	, m_AutoReset(AutoReset)
{
	initialize();
}

f64 StopWatch::GetElapsedMilliseconds()
{
	LARGE_INTEGER li{0};
	QueryPerformanceCounter(&li);
	u64 elapsed = u64(li.QuadPart - m_LastTick.QuadPart);
	f64 interval = (f64)(elapsed) * m_InvFreq * 1000;
	if (m_AutoReset) {
		Reset();
		return interval;
	}
	m_Accum += interval;
	return m_Accum;
}

f64 StopWatch::GetElapsedSeconds()
{
	LARGE_INTEGER li{ 0 };
	QueryPerformanceCounter(&li);
	u64 elapsed = u64(li.QuadPart - m_LastTick.QuadPart);
	f64 interval = (f64)(elapsed)*m_InvFreq;
	if (m_AutoReset) {
		Reset();
		return interval;
	}
	m_Accum += interval;
	return m_Accum;
}

void StopWatch::Reset()
{
	m_Accum = 0.0;
	QueryPerformanceCounter(&m_LastTick);
}

void StopWatch::initialize()
{
	QueryPerformanceFrequency(&m_Freq);
	m_InvFreq = 1.0 / (f64)m_Freq.QuadPart;
	QueryPerformanceCounter(&m_LastTick);

}