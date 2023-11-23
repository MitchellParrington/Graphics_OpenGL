#pragma once
#include "bmpch.hpp"

namespace Bam
{
	struct VertexArrayFormat
	{
		ui32bt size;
		ui32bt offset = 0;
		ui32t index = 0;
		ui32t count = 0;
	};

	struct VertexArray
	{
		ui32t gluid;
	};

	Status BM_API InitVertexArray(VertexArray& va);
	VertexArray BM_API InitVertexArray();
	Status BM_API BindVertexArray(VertexArray& va);
	Status BM_API DeleteVertexArray(VertexArray& va);
	Status BM_API BindVertexArray(ui32t gluid);

	VertexArrayFormat InitVertexArrayFormat(ui32bt size);
	Status BM_API InitVertexArrayFormat(VertexArrayFormat& vaf, ui32bt size);
	Status BM_API FormatVertexArray(VertexArray& va, ui32t index, ui32t count, ui32bt vertexSize, ui32bt offset, b8t norm);
	Status BM_API FormatVertexArray(VertexArray& va, VertexArrayFormat& vaf, ui32t count, b8t = 0);
}