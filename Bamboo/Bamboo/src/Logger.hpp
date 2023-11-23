// INCLUDED IN BMPCH.HPP
#pragma once

#include <memory>

#include "Vendor/Spdlog.hpp"

#include "Types.hpp"

enum class LogLevel {
    trace = SPDLOG_LEVEL_TRACE,
    debug = SPDLOG_LEVEL_DEBUG,
    info = SPDLOG_LEVEL_INFO,
    warn = SPDLOG_LEVEL_WARN,
    err = SPDLOG_LEVEL_ERROR,
    critical = SPDLOG_LEVEL_CRITICAL,
    off = SPDLOG_LEVEL_OFF,
};

using Logger = std::shared_ptr<spdlog::logger>;

extern Logger InitLogger(const char* name);
extern void SetLoggerLevel(Logger logger, LogLevel level);
extern void SetLoggerPattern(Logger logger, const char* pattern);

extern const Logger gCoreLogger;

#define BM_CORE_LOG_FATAL(...) gCoreLogger->critical(__VA_ARGS__)
#define BM_CORE_LOG_ERROR(...) gCoreLogger->error(__VA_ARGS__)
#define BM_CORE_LOG_WARN(...)  gCoreLogger->warn(__VA_ARGS__)
#define BM_CORE_LOG_INFO(...)  gCoreLogger->info(__VA_ARGS__)
#define BM_CORE_LOG_TRACE(...) gCoreLogger->trace(__VA_ARGS__)