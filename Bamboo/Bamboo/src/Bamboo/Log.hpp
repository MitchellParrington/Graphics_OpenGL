// INCLUDED IN BMPCH.HPP
#pragma once
#include "Core.hpp"

#include "Vendor/Spdlog.hpp"

namespace Bam
{
	struct BM_API Log
	{
		static void Init();
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};
}
//
//#ifdef BM_LOG
//	#define BM_CORE_LOG_FATAL(...) Bam::Log::sCoreLogger->critical(__VA_ARGS__)
//	#define BM_CORE_LOG_ERROR(...) Bam::Log::sCoreLogger->error(__VA_ARGS__)
//	#define BM_CORE_LOG_WARN(...)  Bam::Log::sCoreLogger->warn(__VA_ARGS__)
//	#define BM_CORE_LOG_INFO(...)  Bam::Log::sCoreLogger->info(__VA_ARGS__)
//	#define BM_CORE_LOG_TRACE(...) Bam::Log::sCoreLogger->trace(__VA_ARGS__)
//
//	#define BM_FATAL(...) Bam::Log::sClientLogger->critical(__VA_ARGS__)
//	#define BM_ERROR(...) Bam::Log::sClientLogger->error(__VA_ARGS__)
//	#define BM_WARN(...)  Bam::Log::sClientLogger->warn(__VA_ARGS__)
//	#define BM_INFO(...)  Bam::Log::sClientLogger->info(__VA_ARGS__)
//	#define BM_TRACE(...) Bam::Log::sClientLogger->trace(__VA_ARGS__)
//#else
//	#define BM_CORE_LOG_FATAL(...)
//	#define BM_CORE_LOG_ERROR(...)
//	#define BM_CORE_LOG_WARN(...) 
//	#define BM_CORE_LOG_INFO(...) 
//	#define BM_CORE_LOG_DEBUG(...) 
//	#define BM_CORE_LOG_TRACE(...)
//
//	#define BM_FATAL(...)
//	#define BM_ERROR(...)
//	#define BM_WARN(...) 
//	#define BM_INFO(...) 
//	#define BM_DEBUG(...) 
//	#define BM_TRACE(...)
//#endif