#include "bmpch.hpp"
#include "VertexStore.hpp"

#include "Vertex.hpp"

namespace Bam
{
	VertexStore InitVertexStore(ui32t numVertices)
	{
		VertexStore vs;
		vs.count = numVertices;
		vs.size = numVertices * sizeof(Vertex);
		vs.data = new Vertex[numVertices];
		return vs;
	}

	VertexStore InitVertexStore(Vertex* vertices, ui32t numVertices)
	{
		VertexStore vs;
		vs.count = numVertices;
		vs.size = numVertices * sizeof(Vertex);
		vs.data = vertices;
		return vs;
	}

	VertexStore* InitVertexStore(VertexStore* vs, Vertex* vertices, ui32t numVertices)
	{
		vs->count = numVertices;
		vs->size = numVertices * sizeof(Vertex);
		vs->data = vertices;
		return vs;
	}

	VertexStore* InitVertexStore(VertexStore* vs, ui32t numVertices)
	{
		vs->count = numVertices;
		vs->size = numVertices * sizeof(Vertex);
		vs->data = new Vertex[numVertices];
		return vs;
	}

	Status DeleteVertexStore(VertexStore* vs)
	{
		delete[] vs->data;
		return Status::Success;
	}
}