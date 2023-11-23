#include "bmpch.hpp"
#include "Window.hpp"

#include "Vendor/Glfw.hpp"
#include "Vendor/Glad.hpp"

namespace Bam
{
	Window* InitWindow(Window* window)
	{
		glfwInit();

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_RESIZABLE, window->resizable);
		if (window->fullscreen) glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

		window->window = glfwCreateWindow(window->width, window->height, window->title, nullptr, nullptr);

		if (!window->window)
		{
			BM_CORE_LOG_FATAL("Failed to create GLFWwindow instance");
			return nullptr;
		}

		glfwMakeContextCurrent(window->window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			BM_CORE_LOG_FATAL("Failed to initialise OpenGL context");
			return nullptr;
		}

		glfwSwapInterval(window->swapInterval);

#ifdef BAMBOO_CONFIG_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Bam::GLDebugMessageCallback, nullptr);
#endif

		return window;
	}

	Window InitWindow(ui32t width, ui32t height, const char* title, bool resizable, bool fullscreen, ui32t swapInterval)
	{
		Window window;
		window.width = width;
		window.height = height;
		window.title = title;
		window.resizable = resizable;
		window.fullscreen = fullscreen;
		window.swapInterval = swapInterval;

		InitWindow(&window);
		return window;
	}

	bool IsWindowAlive(Window* window)
	{
		if (window->window == nullptr) return false;
		else return true;
	}

	void ExitWindow(Window* window)
	{
		glfwDestroyWindow(window->window);
		glfwTerminate();
	}

	bool ShouldWindowClose(Window* window)
	{
		if (glfwWindowShouldClose(window->window))
			return true; // window should close
		else
			return false; // window should remain open
	}

	void RenderWindow(Window* window)
	{
		glfwSwapBuffers(window->window);
	}

	void UpdateWindow(Window* window)
	{
		glfwPollEvents();

		i32t width, height;
		glfwGetWindowSize(window->window, &width, &height);
		window->width = (ui32t)width;
		window->height = (ui32t)height;
	}



	Status InitWindow(Window& w)
	{
		glfwInit();

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_RESIZABLE, w.resizable);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

		if (w.fullscreen)
			w.window = glfwCreateWindow(w.width, w.height, w.title, monitor, nullptr);
		else
			w.window = glfwCreateWindow(w.width, w.height, w.title, nullptr, nullptr);

		if (!w.window)
		{
			BM_CORE_LOG_FATAL("Failed to create GLFWwindow instance");
			return Status::Fail;
		}

		glfwMakeContextCurrent(w.window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			BM_CORE_LOG_FATAL("Failed to initialise OpenGL context");
			return Status::Fail;
		}

		glfwSwapInterval(w.swapInterval);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Bam::GLDebugMessageCallback, nullptr);

		return Status::Success;
	}

	Status ExitWindow(Window& w)
	{
		glfwDestroyWindow(w.window);
		glfwTerminate();
		return Status::Success;
	}

	Status ShouldWindowClose(Window& w)
	{
		if (glfwWindowShouldClose(w.window))
			return Status::True; // window close
		else
			return Status::False; // dont close window
	}

	Status RenderWindow(Window& w)
	{
		glfwSwapBuffers(w.window);
		return Status::Success;
	}

	Status CheckWindowEvents(Window& w)
	{
		glfwPollEvents();

		i32t width, height;
		glfwGetWindowSize(w.window, &width, &height);
		w.width = (ui32t)width;
		w.height = (ui32t)height;

		return Status::Success;
	}
}