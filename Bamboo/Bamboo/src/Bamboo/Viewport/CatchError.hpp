#pragma once
#include "bmpch.hpp"

namespace Bam
{
	Status BM_API CatchGlError(const char* func, const char* file, int line);

	void __stdcall GLDebugMessageCallback(ui32t source, ui32t type, ui32t id, ui32t severity, i32t length, const char* msg, const void* data);
}

#define BM_CATCH(x) x; Bam::CatchGlError(#x, __FILE__, __LINE__)
//#define BM_CATCH(x) x;