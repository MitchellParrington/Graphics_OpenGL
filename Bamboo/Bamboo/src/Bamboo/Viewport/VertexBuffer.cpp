#include "bmpch.hpp"
#include "VertexBuffer.hpp"

#include "Vendor/Glad.hpp"

#include "BufferAttrib.hpp"
#include "VertexStore.hpp"

namespace Bam
{
	VertexBuffer* InitVertexBuffer(VertexBuffer* vb, ui32bt size, f32ut* data, BufferState use)
	{
		BM_CATCH(glGenBuffers(1, &vb->gluid));
		BM_CATCH(glBindBuffer(GL_ARRAY_BUFFER, vb->gluid));
		BM_CATCH(glBufferData(GL_ARRAY_BUFFER, size, (const void*)data, (ui32t)use));
		return vb;
	}

	VertexBuffer InitVertexBuffer(ui32bt size, f32ut* data, BufferState use)
	{
		VertexBuffer vb;
		BM_CATCH(glGenBuffers(1, &vb.gluid));
		BM_CATCH(glBindBuffer(GL_ARRAY_BUFFER, vb.gluid));
		BM_CATCH(glBufferData(GL_ARRAY_BUFFER, size, (const void*)data, (ui32t)use));
		return vb;
	}

	VertexBuffer InitVertexBuffer(VertexStore* vs, BufferState use)
	{
		VertexBuffer vb;
		BM_CATCH(glGenBuffers(1, &vb.gluid));
		BM_CATCH(glBindBuffer(GL_ARRAY_BUFFER, vb.gluid));
		BM_CATCH(glBufferData(GL_ARRAY_BUFFER, vs->size, (const void*)vs->data, (ui32t)use));
		return vb;
	}

	VertexBuffer* SetVertexBufferData(VertexBuffer* vb, ui32bt offset, ui32bt size, f32ut* data)
	{
		BM_CATCH(glBindBuffer(GL_ARRAY_BUFFER, vb->gluid));
		BM_CATCH(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
		return vb;
	}

	VertexBuffer* DeleteVertexBuffer(VertexBuffer* vb)
	{
		BM_CATCH(glDeleteBuffers(1, &vb->gluid));
		return vb;
	}

	VertexBuffer* BindVertexBuffer(VertexBuffer* vb)
	{
		BM_CATCH(glBindBuffer(GL_ARRAY_BUFFER, vb->gluid));
		return vb;
	}

	Status BindVertexBuffer(ui32t gluid)
	{
		BM_CATCH(glBindBuffer(GL_ARRAY_BUFFER, gluid));
		return Status::Success;
	}
}