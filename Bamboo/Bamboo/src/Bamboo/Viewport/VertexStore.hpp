#pragma once
#include "bmpch.hpp"

namespace Bam
{
	struct Vertex;

	struct VertexStore
	{
		Vertex* data;
		ui32t count;
		ui32bt size;
	};

	//STATIC_STRUCT_SIZE(VertexStore);

	VertexStore InitVertexStore(ui32t numVertices);
	VertexStore InitVertexStore(Vertex* vertices, ui32t numVertices);
	VertexStore* InitVertexStore(VertexStore* vertexStore, Vertex* vertices, ui32t numVertices);
	VertexStore* InitVertexStore(VertexStore* vertexStore, ui32t numVertices);

	Status DeleteVertexStore(VertexStore* vs);
}