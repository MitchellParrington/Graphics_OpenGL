#include "bmpch.hpp"
#include "Timer.hpp"

Precision Timer::globalPrecision = Precision::Milli;
Logger Timer::logger = InitLogger("Timer");

Timer::~Timer()
{
	Timer::Nanoseconds elapsed = GetTimer(*this);
	const char* imp = "{} {}";

	switch (LocalPrecision)
	{
	case Precision::Nano:
		Timer::Nanoseconds nan = std::chrono::duration_cast<Timer::Nanoseconds>(elapsed);
		logger->info(imp, nan, name);
		break;
	case Precision::Micro:
		Timer::Microseconds mic = std::chrono::duration_cast<Timer::Microseconds>(elapsed);
		logger->info(imp, mic, name);
		break;
	case Precision::Milli:
		Timer::Milliseconds mil = std::chrono::duration_cast<Timer::Milliseconds>(elapsed);
		logger->info(imp, mil, name);
		break;
	case Precision::Sec:
		Timer::Seconds sec = std::chrono::duration_cast<Timer::Seconds>(elapsed);
		logger->info(imp, sec, name);
		break;
	case Precision::Min:
		Timer::Minutes min = std::chrono::duration_cast<Timer::Minutes>(elapsed);
		logger->info(imp, min, name);
		break;
	case Precision::Hour:
		Timer::Hours hour = std::chrono::duration_cast<Timer::Hours>(elapsed);
		logger->info(imp, hour, name);
		break;
	default:
		break;
	}
}

Timer InitTimer()
{
	return Timer{ std::chrono::high_resolution_clock::now(), "Unknown", Timer::globalPrecision};
}

Timer InitTimer(const char* name)
{
	return Timer{ std::chrono::high_resolution_clock::now(), name, Timer::globalPrecision };
}

Timer InitTimer(Precision prec)
{
	return Timer{ std::chrono::high_resolution_clock::now(), "Unknown", prec };
}

Timer InitTimer(const char* name, Precision prec)
{
	return Timer{ std::chrono::high_resolution_clock::now(), name, prec };
}

Timer::Nanoseconds GetTimer(Timer& timer)
{

	std::chrono::time_point<std::chrono::steady_clock> start = timer.start;
	std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
	Timer::Nanoseconds elapsed = end.time_since_epoch() - start.time_since_epoch();
	return elapsed;
}