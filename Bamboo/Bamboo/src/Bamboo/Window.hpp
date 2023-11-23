#pragma once
#include "bmpch.hpp"

struct GLFWwindow;

namespace Bam
{
	struct BM_API Window
	{
		ui32t width = 1280;
		ui32t height = 720;
		const char* title = "Bamboo";
		bool resizable = 1;
		bool fullscreen = 1;
		ui32t swapInterval = 1;
		GLFWwindow* window = nullptr;
	};

	// NEW

	Window InitWindow(ui32t width, ui32t height, const char* title, bool resizable, bool fullscreen, ui32t swapInterval);
	Window* InitWindow(Window* window);
	void ExitWindow(Window* window);
	bool ShouldWindowClose(Window* window);
	void RenderWindow(Window* window);
	void UpdateWindow(Window* window);
	bool IsWindowAlive(Window* window);
	
	// OLD

	Status BM_API InitWindow(Window&);
	Status BM_API ExitWindow(Window&);
	Status BM_API ShouldWindowClose(Window&);
	Status BM_API RenderWindow(Window&);
	Status BM_API CheckWindowEvents(Window&);

}