#pragma once
#include "bmpch.hpp"

#include "Vendor/Imgui.hpp"

namespace Bam
{
	struct Window;

	struct Gui
	{
		bool keyboard = 1;
		bool docking = 1;
		bool multiViewport = 1;
		bool dark = 1;
		const char* shaderVersion = "#version 450";
		ImGuiIO* io = nullptr;
	};

	Status BM_API InitGui(Window&, Gui&);
	Status BM_API LinkGuiToWindow(Window&);
	Status BM_API ExitGui(Gui&);
	Status BM_API StartGuiFrame();
	Status BM_API RenderGui(Gui&);
}