#include "bmpch.hpp"
#include "IndexStore.hpp"

namespace Bam
{
	IndexStore InitIndexStore(ui32t numIndices)
	{
		IndexStore is;
		is.count = numIndices;
		is.size = numIndices * sizeof(ui32t);
		is.data = new ui32t[numIndices];
		return is;
	}

	IndexStore InitIndexStore(ui32t* indices, ui32t numIndices)
	{
		IndexStore is;
		is.count = numIndices;
		is.size = numIndices * sizeof(ui32t);
		is.data = indices;
		return is;
	}

	IndexStore* InitIndexStore(IndexStore* is, ui32t* indices, ui32t numIndices)
	{
		is->count = numIndices;
		is->size = numIndices * sizeof(ui32t);
		is->data = indices;
		return is;
	}

	IndexStore* InitIndexStore(IndexStore* is, ui32t numIndices)
	{
		is->count = numIndices;
		is->size = numIndices * sizeof(ui32t);
		is->data = new ui32t[numIndices];
		return is;
	}

	Status DeleteIndexStore(IndexStore* is)
	{
		delete[] is->data;
		return Status::Success;
	}
}