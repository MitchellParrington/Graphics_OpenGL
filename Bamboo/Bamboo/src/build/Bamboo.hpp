#pragma once

#include "bmpch.hpp"
#include "Core.hpp"
#include "Types.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

//#include "Vendor/Vendor.hpp"
#include "Vendor/Glfw.hpp"
#include "Vendor/Glad.hpp"
#include "Vendor/Imgui.hpp"
#include "Vendor/Assimp.hpp"
#include "Vendor/Entt.hpp"
#include "Vendor/Glm.hpp"
#include "Vendor/Spdlog.hpp"
#include "Vendor/Stbimage.hpp"

#include "Bamboo/Log.hpp" // compatability
#include "Bamboo/Status.hpp"
#include "Bamboo/Async.hpp"
#include "Bamboo/Buffer.hpp"
#include "Bamboo/Mesh.hpp"
#include "Bamboo/Renderer.hpp"
#include "Bamboo/Transform.hpp"
#include "Bamboo/Vec.hpp"
#include "Bamboo/Window.hpp"
#include "Bamboo/Shader.hpp"
#include "Bamboo/thingtodraw.hpp"

#include "Bamboo/Viewport/Viewport.hpp"
#include "Bamboo/Viewport/Primitive.hpp"
#include "Bamboo/Viewport/CatchError.hpp"
#include "Bamboo/Viewport/Vertex.hpp"
#include "Bamboo/Viewport/BufferAttrib.hpp"
#include "Bamboo/Viewport/FrameBuffer.hpp"
#include "Bamboo/Viewport/VertexArray.hpp"
#include "Bamboo/Viewport/IndexBuffer.hpp"
#include "Bamboo/Viewport/VertexBuffer.hpp"
#include "Bamboo/Viewport/IndexStore.hpp"
#include "Bamboo/Viewport/VertexStore.hpp"
#include "Bamboo/Viewport/Uniform.hpp"

#include "Bamboo/Gui/Gui.hpp"

#include "Bamboo/Asset/Model.hpp"
#include "Bamboo/Asset/LoadModel.hpp"

#include "main.hpp"

#define BAMBOO_HAVE_MAIN
// #define BAMBOO_HAVE_EDITOR

#ifdef BAMBOO_HAVE_MAIN
int main(int argc, char** argv)
#ifdef BAMBOO_HAVE_EDITOR
{
	bamboocore_main_forrest(argc, argv);
	return 0;
}
#else
{
	bamboocore_main_standalone(argc, argv);
	return 0;
}
#endif
#endif // BAMBOO_HAVE_MAIN


// OLD

// DLL Entry Point
// Keep at bottom of file
//
//#if defined(BM_PLATFORM_WINDOWS) && defined(BM_DLL)
//
//extern int bam_main(void);
//int main(int argc, char** argv)
//{
//	Bam::Log::Init();
//	BM_CORE_LOG_FATAL("CORE BEGIN");
//
//	int r = bam_main();
//
//	BM_CORE_LOG_FATAL("CORE EXIT");
//	return r;
//}
//
//#endif // BM_PLATFORM_WINDOWS