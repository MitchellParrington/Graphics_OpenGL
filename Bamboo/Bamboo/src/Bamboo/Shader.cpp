#include "bmpch.hpp"
#include "Shader.hpp"

#include "Vendor/Glad.hpp"

namespace Bam
{

	Status BindShader(ui32t gluid)
	{
		BM_CATCH(glUseProgram(gluid));
		return Status::Success;
	}

	Status BindShader(Shader s)
	{
		BM_CATCH(glUseProgram(s.gluid));
		return Status::Success;
	}

	Status DeleteShader(Shader& s)
	{
		BM_CATCH(glDeleteProgram(s.gluid));
		return Status::Success;
	}

	Status InitShader(Shader& s, ShaderSource& ss)
	{
		ui32t sp = BM_CATCH(glCreateProgram());
		s.gluid = sp;

		for (ui32t i = 0; i < ss.length; i++)
		{
			BM_CATCH(glAttachShader(sp, ss.gluid[i]));
		}
		BM_CATCH(glLinkProgram(sp));

		i32t linkSuccess;
		BM_CATCH(glGetProgramiv(sp, GL_LINK_STATUS, &linkSuccess));
		if (linkSuccess == GL_FALSE) // Shader Linking Failed
		{
			i32t errorMessageLength;
			BM_CATCH(glGetProgramiv(sp, GL_INFO_LOG_LENGTH, &errorMessageLength));
			char* errorMessage = (char*)_malloca(errorMessageLength * sizeof(char));
			BM_CATCH(glGetProgramInfoLog(sp, errorMessageLength, &errorMessageLength, errorMessage));

			BM_CORE_WARN("Shader Linking failed : {}", errorMessage);
			return Status::Fail;
		}

		for (ui32t i = 0; i < ss.length; i++)
		{
			BM_CATCH(glDetachShader(sp, ss.gluid[i]));
		}

		return Status::Success;
	}

	Status InitShaderSource(ShaderSource& ss, ui32t length)
	{
		ss.length = length;
		ui32t bufferSize = length * (sizeof(const char*) + sizeof(ShaderType) + sizeof(ui32t));
		unsigned char* buffer = new unsigned char[bufferSize] {0};
		ss.files = (const char**)(buffer);
		ss.types = (ShaderType*)(ss.files + length);
		ss.gluid = (ui32t*)(ss.types + length);
		return Status::Success;
	}

	Status CompileShaderSource(ShaderSource& ss)
	{
		//BM_PROFILE_PREC("S:CompileShaderSource", Bam::Precision::Milli);
		for (ui32t i = 0; i < ss.length; i++)
		{
			std::string shaderSource;
			ParseShader(ss.files[i], shaderSource);
			if (GenShader(shaderSource.c_str(), ss.types[i], ss.gluid[i]) == Status::Fail)
				return Status::Fail;
		}
		return Status::Success;
	}

	Status DeleteShaderSource(ShaderSource& ss)
	{
		for (ui32t i = 0; i < ss.length; i++)
		{
			BM_CATCH(glDeleteShader(ss.gluid[i]));
		}
		delete[] (unsigned char*)ss.files;
		return Status::Success;
	}

	Status ParseShader(const char* filepath, std::string& string)
	{
		std::ifstream in{ filepath, std::ifstream::in };
		std::ostringstream sstr;
		sstr << in.rdbuf();
		string = sstr.str();
		return Status::Success;
	}

	Status GenShader(const char* source, ShaderType type, ui32t& shaderGluid)
	{
		shaderGluid = glCreateShader((ui32t)type);
		BM_CATCH(glShaderSource(shaderGluid, 1, &source, nullptr));
		BM_CATCH(glCompileShader(shaderGluid));

		i32t shaderCompileSuccess;
		BM_CATCH(glGetShaderiv(shaderGluid, GL_COMPILE_STATUS, &shaderCompileSuccess));
		if (shaderCompileSuccess == GL_FALSE)
		{
			i32t errorMessageLength;
			BM_CATCH(glGetShaderiv(shaderGluid, GL_INFO_LOG_LENGTH, &errorMessageLength));
			char* errorMessage = (char*)_malloca(errorMessageLength * sizeof(char));
			BM_CATCH(glGetShaderInfoLog(shaderGluid, errorMessageLength, &errorMessageLength, errorMessage));
			BM_CATCH(glDeleteShader(shaderGluid));

			BM_CORE_WARN("Shader {} compilation failed : {}", type, errorMessage);
			return Status::Fail;
		}
		return Status::Success;
	}
}