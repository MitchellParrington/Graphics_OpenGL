#pragma once
#include "bmpch.hpp"

namespace Bam
{
	extern struct Window;

	struct Viewport
	{
		ui32t x = 0;
		ui32t y = 0;
		ui32t width = 256;
		ui32t height = 256;
	};

	// NEW

	Viewport InitViewport(ui32t x, ui32t y, ui32t width, ui32t height);
	Viewport InitViewport(Window* window);
	Viewport* UpdateViewport(Viewport* viewport);

	// OLD

	Status BM_API SetViewport(Viewport&);
	Status BM_API SetViewportRaw(ui32t, ui32t, ui32t, ui32t);
	Status BM_API SetViewportIfDifferent(Viewport&, ui32t, ui32t, ui32t, ui32t);
}