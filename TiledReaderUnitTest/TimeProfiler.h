#ifndef TOOL_TIME_PROFILER_H_
#define TOOL_TIME_PROFILER_H_

#if (defined(_WIN32) || defined(_WIN64))

#include <stdio.h>
#include <iostream>
#include <Windows.h>

namespace priv
{
	class TimeProfiler
	{
	public:
		TimeProfiler(const char* str, ...);
		~TimeProfiler();

	private:
		char m_buffer[256];
		LARGE_INTEGER m_frequency; // CPU ticks per second
		LARGE_INTEGER m_start;
		LARGE_INTEGER m_end;
	};
}

#endif

// Profile only if debugging at windows platforms only. 
// This profiles the time spent to process the block that this macro was called within
#if (defined(_WIN32) || defined(_WIN64))
#ifndef TIME_PROFILER
#define TIME_PROFILER(str, ...) priv::TimeProfiler watcher__(str, __VA_ARGS__)
#endif // TIME_PROFILER
#else
// If not debugging, do nothing
#ifndef TIME_PROFILER
#define TIME_PROFILER(str) do { } while(0) // This avoids empty statements
#endif // TIME_PROFILER
#endif // _DEBUG

#endif // File guards