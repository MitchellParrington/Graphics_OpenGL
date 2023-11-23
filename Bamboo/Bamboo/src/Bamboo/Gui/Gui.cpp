#include "bmpch.hpp"
#include "Gui.hpp"

#include "Vendor/Imgui.hpp"
#include "Vendor/Glfw.hpp"

#include "Bamboo/Window.hpp"

namespace Bam
{
	Status InitGui(Window& w, Gui& g)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		g.io = &ImGui::GetIO(); (void)*g.io;

		if (g.keyboard)
			g.io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		
		if (g.docking)
			g.io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
		
		if (g.multiViewport)
			g.io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
		
		if (g.dark)
			ImGui::StyleColorsDark();
		else
			ImGui::StyleColorsLight();

		ImGui_ImplGlfw_InitForOpenGL(w.window, true);
		ImGui_ImplOpenGL3_Init(g.shaderVersion);
		
		return Status::Success;
	}

	Status LinkGuiToWindow(Window& w)
	{
		ImGui_ImplGlfw_InitForOpenGL(w.window, true);
		return Status::Success;
	}

	Status StartGuiFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		return Status::Success;
	}

	Status RenderGui(Gui& g)
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (g.io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		return Status::Success;
	}

	Status ExitGui(Gui& g)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		return Status::Success;
	}
}