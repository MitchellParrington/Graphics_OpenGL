#pragma once
#include "bmpch.hpp"

#include "Vendor/Glad.hpp"

namespace Bam
{
	enum class BM_API BufferState
	{
		DynamicDraw = 0x88E8,
		StaticDraw = 0x88E4
	};
}