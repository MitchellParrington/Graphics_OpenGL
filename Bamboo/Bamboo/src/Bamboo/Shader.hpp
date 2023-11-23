#pragma once
#include "bmpch.hpp"

#include "Vendor/Glad.hpp"

namespace Bam
{
	enum class BM_API ShaderType
	{
		Vertex = 0x8B31,
		TessControll = 0x8E88,
		TessEval = 0x8E87,
		Geometry = 0x8DD9,
		Fragment = 0x8B30,
		Compute = 0x91B9
	};

	struct BM_API ShaderSource
	{
		const char** files;
		ShaderType* types;
		ui32t* gluid;
		ui32t length;
	};

	struct BM_API Shader
	{
		ui32t gluid;
	};

	Status BM_API InitShader(Shader&, ShaderSource&);
	Status BM_API BindShader(Shader);
	Status BM_API BindShader(ui32t);
	Status BM_API DeleteShader(Shader&);

	Status BM_API InitShaderSource(ShaderSource& ss, ui32t length);
	Status BM_API CompileShaderSource(ShaderSource& ss);
	Status BM_API DeleteShaderSource(ShaderSource& ss);
	Status BM_API ParseShader(const char* filepath, std::string& out);
	Status BM_API GenShader(const char* source, ShaderType type, ui32t& gluid);	
}