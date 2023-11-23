#include "bmpch.hpp"
#include "IndexBuffer.hpp"

#include "Vendor/Glad.hpp"

#include "IndexStore.hpp"

namespace Bam
{
	IndexBuffer* InitIndexBuffer(IndexBuffer* ib, ui32bt size, ui32t* data, BufferState use)
	{
		ib->count = size / sizeof(ui32t);
		BM_CATCH(glGenBuffers(1, &ib->gluid));
		BM_CATCH(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->gluid));
		BM_CATCH(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (const void*)data, (ui32t)use));
		return ib;
	}

	IndexBuffer InitIndexBuffer(ui32bt size, ui32t* data, BufferState use)
	{
		IndexBuffer ib;
		ib.count = size / sizeof(ui32t);
		BM_CATCH(glGenBuffers(1, &ib.gluid));
		BM_CATCH(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.gluid));
		BM_CATCH(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (const void*)data, (ui32t)use));
		return ib;
	}

	IndexBuffer InitIndexBuffer(IndexStore* is, BufferState use)
	{
		IndexBuffer ib;
		ib.count = is->count;
		BM_CATCH(glGenBuffers(1, &ib.gluid));
		BM_CATCH(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.gluid));
		BM_CATCH(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib.count * sizeof(ui32t), (const void*)is->data, (ui32t)use));
		return ib;
	}

	IndexBuffer* SetIndexBufferData(IndexBuffer* ib, ui32bt offset, ui32bt size, ui32t* data)
	{
		BM_CATCH(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->gluid));
		BM_CATCH(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, (const void*)data));
		return ib;
	}

	IndexBuffer* DeleteIndexBuffer(IndexBuffer* ib)
	{
		BM_CATCH(glDeleteBuffers(1, &ib->gluid));
		return ib;
	}

	IndexBuffer* BindIndexBuffer(IndexBuffer* ib)
	{
		BM_CATCH(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->gluid));
		return ib;
	}

	Status BindIndexBuffer(ui32t gluid)
	{
		BM_CATCH(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gluid));
		return Status::Success;
	}
}