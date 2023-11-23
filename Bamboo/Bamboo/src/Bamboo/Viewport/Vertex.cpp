#include "bmpch.hpp"
#include "Vertex.hpp"

#include "Bamboo/Vec.hpp"

namespace Bam
{
	Vertex InitVertex(Float3 pos, Float3 norm, Float3 tex, Float3 tan, Float3 bit, Float4 col)
	{
		return { pos, norm, tex, tan, bit, col };
	}

	Vertex* InitVertex(Vertex* v, Float3* pos, Float3* norm, Float3* tex, Float3* tan, Float3* bit, Float4* col)
	{
		v->position = *pos;
		v->normal = *norm;
		v->texCoords = *tex;
		v->tangents = *tan;
		v->bitangents = *bit;
		v->color = *col;
		return v;
	}

	Vertex* InitVertex(Vertex* v, Float3 pos, Float3 norm, Float3 tex, Float3 tan, Float3 bit, Float4 col)
	{
		v->position = pos;
		v->normal = norm;
		v->texCoords = tex;
		v->tangents = tan;
		v->bitangents = bit;
		v->color = col;
		return v;
	}
}