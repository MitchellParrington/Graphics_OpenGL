#include "bmpch.hpp"
#include "VertexArray.hpp"

#include "Vendor/Glad.hpp"

namespace Bam
{
	Status BindVertexArray(VertexArray& va)
	{
		BM_CATCH(glBindVertexArray(va.gluid));
		return Status::Success;
	}
	Status BindVertexArray(ui32t gluid)
	{
		BM_CATCH(glBindVertexArray(gluid));
		return Status::Success;
	}
	
	Status InitVertexArray(VertexArray& va)
	{
		BM_CATCH(glGenVertexArrays(1, &va.gluid));
		BM_CATCH(glBindVertexArray(va.gluid));
		return Status::Success;
	}

	VertexArray InitVertexArray()
	{
		VertexArray va;
		BM_CATCH(glGenVertexArrays(1, &va.gluid));
		BM_CATCH(glBindVertexArray(va.gluid));
		return va;
	}

	Status DeleteVertexArray(VertexArray& va)
	{
		BM_CATCH(glDeleteVertexArrays(1, &va.gluid));
		return Status::Success;
	}

	VertexArrayFormat InitVertexArrayFormat(ui32bt size)
	{
		return { size };
	}

	Status InitVertexArrayFormat(VertexArrayFormat& vaf, ui32bt size)
	{
		vaf.size = size;
		return Status::Success;
	}

	Status FormatVertexArray(VertexArray& va, ui32t index, ui32t count, ui32bt vertexSize, ui32bt offset, b8t norm)
	{
		BM_CATCH(glBindVertexArray(va.gluid));
		BM_CATCH(glEnableVertexAttribArray(index));
		BM_CATCH(glVertexAttribPointer(index, count, GL_FLOAT, norm, vertexSize, (const void*)offset));
		return Status::Success;
	}

	Status FormatVertexArray(VertexArray& va, VertexArrayFormat& vaf, ui32t count, b8t norm)
	{
		BM_CATCH(glBindVertexArray(va.gluid));
		BM_CATCH(glEnableVertexAttribArray(vaf.index));
		BM_CATCH(glVertexAttribPointer(vaf.index, count, GL_FLOAT, norm, vaf.size, (const void*)vaf.offset));
		vaf.index += 1;
		vaf.offset += sizeof(f32ut) * count;
		return Status::Success;
	}
}