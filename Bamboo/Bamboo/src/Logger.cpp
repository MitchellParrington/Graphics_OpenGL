#include "bmpch.hpp"
#include "Logger.hpp"

const Logger gCoreLogger = InitLogger("CORE");

Logger InitLogger(const char* name) 
{
	Logger logger = spdlog::stdout_color_mt(name);
	logger->set_level((spdlog::level::level_enum)LogLevel::trace);
	logger->set_pattern("[%T.%e] %^[%n] [%L]%$: %v");
	return logger;
}

void SetLoggerLevel(Logger logger, LogLevel level)
{
	logger->set_level((spdlog::level::level_enum)level);
}

void SetLoggerPattern(Logger logger, const char* pattern)
{
	logger->set_pattern(pattern);
}