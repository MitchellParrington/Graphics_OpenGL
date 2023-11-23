#pragma once
#include "bmpch.hpp"

namespace Bam
{
	struct BM_API Buffer
	{
		const ui32bt size;
		void* const data;
	};

	Buffer BM_API InitBuffer(const ui32bt size, void* const data);
	Buffer BM_API InitBuffer(ui32bt size);
	Status BM_API DeleteBuffer(Buffer& buffer);
}