// INCLUDED IN BMPCH.HPP
#pragma once

#include <chrono>

#include "Types.hpp"
#include "Logger.hpp"

enum class Precision
{
	Nano,
	Micro,
	Milli,
	Sec,
	Min,
	Hour,
};

class Timer
{
public:
	~Timer();

	static Precision globalPrecision;
	static Logger logger;

	std::chrono::time_point<std::chrono::steady_clock> start;
	const char* name;
	Precision LocalPrecision = Precision::Micro;

public:
	using Nanoseconds = std::chrono::duration<i64t, std::ratio<1, 1000000000>>;
	using Microseconds = std::chrono::duration<i64t, std::ratio<1, 1000000>>;
	using Milliseconds = std::chrono::duration<i64t, std::ratio<1, 1000>>;
	using Seconds = std::chrono::duration<i64t, std::ratio<1, 1>>;
	using Minutes = std::chrono::duration<i64t, std::ratio<60, 1>>;
	using Hours = std::chrono::duration<i64t, std::ratio<3600, 1>>;

};

Timer InitTimer();
Timer InitTimer(const char* name);
Timer InitTimer(Precision prec);
Timer InitTimer(const char* name, Precision prec);
Timer::Nanoseconds GetTimer(Timer& timer);


#define BM_PROFILE(name) Timer UNIQUE_NAME(_bam_timer_profile) = InitTimer(name)
#define BM_PROFILE_PREC(name, prec) Timer UNIQUE_NAME(_bam_timer_profile) = InitTimer(name, prec)
#define BM_PROFILE_FUNC(name, func) { BM_PROFILE(name); func; }
#define BM_PROFILE_FUNC_PREC(name, prec, func) { BM_PROFILE_PREC(name, prec); func; }