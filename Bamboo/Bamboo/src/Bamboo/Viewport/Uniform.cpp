#include "bmpch.hpp"
#include "Uniform.hpp"

#include "Vendor/Glad.hpp"

namespace Bam
{
	i32t GetUniformLocation(ui32t sp, const char* name)
	{
		i32t uniform = BM_CATCH(glGetUniformLocation(sp, name));
		return uniform;
	}
}