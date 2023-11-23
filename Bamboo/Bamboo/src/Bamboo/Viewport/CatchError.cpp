#include "bmpch.hpp"
#include "CatchError.hpp"

#include "Vendor/Glad.hpp"
#include "Vendor/Glfw.hpp"

namespace Bam
{
	Status CatchGlError(const char* func, const char* file, int line)
	{
#ifdef BAMBOO_CONFIG_DEBUG
		Status status = Status::Success;
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			BM_CORE_LOG_ERROR("Opengl: {} {} {} {}", error, func, file, line);
			status = Status::Fail;
		}
		return status;
#endif
	}

    // Callback function for printing debug statements
    void __stdcall GLDebugMessageCallback(ui32t source, ui32t type, ui32t id,
        ui32t severity, i32t length,
        const char* msg, const void* data)
    {
#ifdef BAMBOO_CONFIG_DEBUG
        const char* _source;
        const char* _type;
        const char* _severity;

        switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "UNKNOWN";
            break;

        default:
            _source = "UNKNOWN";
            break;
        }

        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER";
            break;

        default:
            _type = "UNKNOWN";
            break;
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            _severity = "HIGH";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            _severity = "MEDIUM";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            _severity = "LOW";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            _severity = "NOTIFICATION";
            break;

        default:
            _severity = "UNKNOWN";
            break;
        }

        printf("OpenGL error [%d]: %s of %s severity, raised from %s: %s\n",
            id, _type, _severity, _source, msg);

        //if (_severity != "NOTIFICATION") {
        //    printf("OpenGL error [%d]: %s of %s severity, raised from %s: %s\n",
        //        id, _type, _severity, _source, msg);
        //}
#endif // BAMBOO_CONFIG_DEBUG
    }
}