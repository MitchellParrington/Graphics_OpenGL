#pragma once
#include "bmpch.hpp"

namespace Bam
{
	enum class BufferState;
	struct IndexStore;

	struct BM_API IndexBuffer
	{
		ui32t count = 0;
		ui32t gluid = 0;
	};

	BM_API IndexBuffer* InitIndexBuffer(IndexBuffer* ib, ui32bt size, ui32t* data, BufferState use);
	BM_API IndexBuffer  InitIndexBuffer(ui32bt size, ui32t* data, BufferState use);
	BM_API IndexBuffer  InitIndexBuffer(IndexStore* is, BufferState use);
	BM_API IndexBuffer* SetIndexBufferData(IndexBuffer* ib, ui32bt offset, ui32bt size, ui32t* data);
	BM_API IndexBuffer* DeleteIndexBuffer(IndexBuffer* ib);
	BM_API IndexBuffer* BindIndexBuffer(IndexBuffer* ib);
	BM_API Status		BindIndexBuffer(ui32t gluid);
}