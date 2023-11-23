#pragma once

#if defined(BAMBOO_SYSTEM_WINDOWS)
	#if defined(BM_DLL)
		#define BM_DLLEXPORT __declspec(dllexport)
		#define BM_DLLIMPORT __declspec(dllimport)
		#if defined(BM_BUILD_DLL)
			#define BM_API BM_DLLEXPORT
		#else
			#define BM_API BM_DLLIMPORT
		#endif
	#else
		#define BM_API
	#endif
#else
	#error Only Windows Supported
#endif

// SET OPTION FLAGS DEPENDING ON BUILD CONFIGURATION

#if defined(BAMBOO_CONFIG_DEBUG)
	#define BAMBOO_ENABLE_ASSERTS
	#define BAMBOO_ENABLE_LOGGING
#endif

#if defined(BAMBOO_CONFIG_RELEASE)
	#define BAMBOO_ENABLE_ASSERTS
#endif

#if defined(BAMBOO_CONFIG_DIST)
#endif

#if defined(BM_GRAPHICS_API_OPENGL) && !defined(GLFW_INCLUDE_NONE)
	#define GLFW_INCLUDE_NONE
#endif

#if defined(BM_PLATFORM_WINDOWS) && !defined(WIN32_LEAN_AND_MEAN)
	#define WIN32_LEAN_AND_MEAN
#endif

#if defined(BAMBOO_CONFIG_DEBUG)
	#define BM_EXIT() __debugbreak(); exit(-1); abort()
	#define BM_ABORT() __debugbreak(); abort()
	#define BM_LOG
#else
	#define BM_EXIT() exit(-1); abort()
	#define BM_ABORT() abort()
#endif

#if defined(BAMBOO_ENABLE_ASSERTS)
	#define BM_CORE_ASSERT(x, ...) { if(!(x)) { BM_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BM_EXIT(); } }
	#define BM_ASSERT(x, ...) { if(!(x)) { BM_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BM_EXIT(); } }
#else
	#define BM_CORE_ASSERT(x, ...)
	#define BM_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#if defined(BM_GRAPHICS_API_OPENGL) && defined(BM_GRAPHICS_API_VULKAN)
#error Only 1 Graphics API can be used at once
#endif


#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b

#define UNIQUE_NAME(base) CONCAT(base, CONCAT(__COUNTER__, __LINE__))

#define STATIC_STRUCT_SIZE(type) char(*__kaboom)[sizeof(type)] = 1;