#pragma once
#include "bmpch.hpp"

namespace Bam
{
	enum class BufferState;
	struct VertexStore;

	struct BM_API VertexBuffer
	{
		ui32t gluid = 0;
	};

	BM_API VertexBuffer* InitVertexBuffer(VertexBuffer* vb, ui32bt size, f32ut* data, BufferState use);
	BM_API VertexBuffer  InitVertexBuffer(ui32bt size, f32ut* data, BufferState use);
	BM_API VertexBuffer  InitVertexBuffer(VertexStore* vs, BufferState use);
	BM_API VertexBuffer* SetVertexBufferData(VertexBuffer* vb, ui32bt offset, ui32bt size, f32ut* data);
	BM_API VertexBuffer* DeleteVertexBuffer(VertexBuffer* vb);
	BM_API VertexBuffer* BindVertexBuffer(VertexBuffer* vb);
	BM_API Status		 BindVertexBuffer(ui32t gluid);
}