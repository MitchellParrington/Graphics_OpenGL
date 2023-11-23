#include "bmpch.hpp"
#include "Buffer.hpp"

namespace Bam
{
	Buffer InitBuffer(const ui32bt size, void* const data)
	{
		return Buffer{ size, data };
	}

	Buffer InitBuffer(ui32bt size)
	{
		void* data = new byte[size]{ 0 };
		return Buffer{ size, data };
	}

	Status DeleteBuffer(Buffer& buffer)
	{
		delete[] buffer.data;
		return Status::Success;
	}
}