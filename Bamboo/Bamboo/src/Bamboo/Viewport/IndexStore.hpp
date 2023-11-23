#pragma once
#include "bmpch.hpp"

namespace Bam
{
	struct BM_API IndexStore
	{
		ui32t* data;
		ui32t count;
		ui32bt size;
	};

	IndexStore InitIndexStore(ui32t numIndices);
	IndexStore InitIndexStore(ui32t* indices, ui32t numIndices);
	IndexStore* InitIndexStore(IndexStore* is, ui32t* indices, ui32t numIndices);
	IndexStore* InitIndexStore(IndexStore* is, ui32t numIndices);
	Status DeleteIndexStore(IndexStore* is);

	//STATIC_STRUCT_SIZE(IndexStore);
}