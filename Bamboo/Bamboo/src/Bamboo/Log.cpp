#include "bmpch.hpp"
#include "Log.hpp"

namespace Bam
{
	std::shared_ptr<spdlog::logger> Log::sCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sClientLogger;

	void Log::Init()
	{
		sCoreLogger = spdlog::stdout_color_mt("CORE");
		sCoreLogger->set_level(spdlog::level::trace);
		sCoreLogger->set_pattern("[%T.%e] %^[ %n ] [%L]%$: %v");

		sClientLogger = spdlog::stdout_color_mt("CLIENT");
		sClientLogger->set_level(spdlog::level::trace);
		sClientLogger->set_pattern("[%T.%e] %^[%n] [%L]%$: %v");
	}
}