#include "TimeProfiler.h"

namespace priv
{
	TimeProfiler::TimeProfiler(const char* str, ...)
	{
		va_list args;

		va_start(args, str);
		vsnprintf(m_buffer, strlen(m_buffer), str, args);
		va_end(args);

		QueryPerformanceFrequency(&m_frequency);
		QueryPerformanceCounter(&m_start);
	}

	TimeProfiler::~TimeProfiler()
	{
		// Query end time before calculating the overhead
		QueryPerformanceCounter(&m_end);

		LARGE_INTEGER overheadStart;
		LARGE_INTEGER overheadStop;

		// Calculate the overhead after the end timer has already been retrieved
		QueryPerformanceCounter(&overheadStart);
		QueryPerformanceCounter(&overheadStop);

		LONGLONG overhead = overheadStart.QuadPart - overheadStop.QuadPart;

		// Log
		printf("%s has taken %.5f milliseconds \n", m_buffer, (m_end.QuadPart - m_start.QuadPart - overhead) * 1000.0 / m_frequency.QuadPart);
	}
}