#pragma once

#ifndef MAIN_HPP
#define MAIN_HPP

namespace Bam
{
	struct FrameBuffer;
	struct Window;
}

extern int bambooclient_setup(int argc, char** argv, Bam::Window* window, Bam::FrameBuffer* renderTarget);
extern int bambooclient_frame(int argc, char** argv, Bam::Window* window, Bam::FrameBuffer* renderTarget);

extern int bamboocore_main_standalone		(int argc, char** argv);
extern int bamboocore_loop_standalone		(int argc, char** argv);

extern int bamboocore_main_forrest			(int argc, char** argv);
extern int bamboocore_loop_forrest			(int argc, char** argv);

#endif // !MAIN_HPP
