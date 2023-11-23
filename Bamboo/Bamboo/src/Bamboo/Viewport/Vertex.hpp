#pragma once
#include "bmpch.hpp"

#include "Bamboo/Vec.hpp"

namespace Bam
{
	struct BM_API Vertex
	{
		Float3 position;
		Float3 normal;
		Float3 texCoords;
		Float3 tangents;
		Float3 bitangents;
		Float4 color;
	};

	static_assert(sizeof(Vertex) == 19 * sizeof(f32ut), "Vertex not tightly packed");

	Vertex InitVertex(Float3 pos, Float3 norm, Float3 tex, Float3 tan, Float3 bit, Float4 col);
	Vertex* InitVertex(Vertex* v, Float3* pos, Float3* norm, Float3* tex, Float3* tan, Float3* bit, Float4* col);
	Vertex* InitVertex(Vertex* v, Float3 pos, Float3 norm, Float3 tex, Float3 tan, Float3 bit, Float4 col);
}