#pragma once
#include "bmpch.hpp"

//#include "Vendor/Glad.hpp"

namespace Bam
{
	BM_API i32t GetUniformLocation(ui32t sp, const char* name);
}

#define SetUniform(degree, type, sp, name, ...) { i32t ul = Bam::GetUniformLocation(sp, name); if (ul >= 0) glUniform##degree##type(ul, __VA_ARGS__); }
#define SetUniformV(degree, type, sp, name, ...) { i32t ul = Bam::GetUniformLocation(sp, name); if (ul >= 0) glUniform##degree##type##v(ul, __VA_ARGS__); }
#define SetUniformMatV(degree, type, sp, name, mat) { i32t ul = Bam::GetUniformLocation(sp, name); if (ul >= 0) glUniformMatrix##degree##type##v(ul, 1, GL_FALSE, mat); }