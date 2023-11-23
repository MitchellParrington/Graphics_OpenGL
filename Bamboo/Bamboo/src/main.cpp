#include "bmpch.hpp"

#include "main.hpp"

#include <gl/GL.h>

#include "Logger.hpp"
#include "Bamboo/Status.hpp"
#include "Bamboo/Window.hpp"
#include "Bamboo/Viewport/FrameBuffer.hpp"
#include "Bamboo/Viewport/Viewport.hpp"



int bamboocore_loop_standalone(int argc, char** argv)
{
	Bam::Window mainWindow;
	mainWindow.title = "Bamboo Client Application";
	if (InitWindow(&mainWindow)->window == nullptr)
	{
		Bam::ExitWindow(&mainWindow);
		BM_EXIT();
	}

	Bam::Viewport mainViewport = Bam::InitViewport(&mainWindow);
	Bam::FrameBuffer mainRenderTarget = Bam::InitFrameBuffer(&mainViewport);
	BM_CORE_ASSERT(Bam::IsFrameBufferComplete(&mainRenderTarget), "Main Render Target (frame buffer) incomplete");

	bambooclient_setup(argc, argv, &mainWindow, &mainRenderTarget);
	
	while (Bam::ShouldWindowClose(&mainWindow) == false)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Bam::BindFrameBuffer(&mainRenderTarget);
		bambooclient_frame(argc, argv, &mainWindow, &mainRenderTarget);
		Bam::BindFrameBuffer((gluid)0);


	}
}

int bamboocore_main_standalone(int argc, char** argv)
#ifdef BAMBOO_CONFIG_DEBUG
{
	BM_PROFILE_PREC("F : bamboo_main_standalone #DEBUG", Precision::Sec);
	SetLoggerLevel(gCoreLogger, LogLevel::trace);
	bamboocore_loop_standalone(argc, argv);
	return 0;
}
#elif BAMBOO_CONFIG_RELEASE
{
	bamboocore_loop_standalone(argc, argv);
	return 0;
}
#elif BAMBOO_CONFIG_DIST
{
	bamboocore_loop_standalone(argc, argv);
	return 0;
}
#else
{
	return -1;
}
#endif

int bamboocore_main_forrest(int argc, char** argv)
{

}
