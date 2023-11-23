#include "bmpch.hpp"
#include "Viewport.hpp"

#include "Vendor/Glad.hpp"

#include "Bamboo/Window.hpp"

namespace Bam
{

	Viewport InitViewport(Window* window)
	{
		return Viewport{ 0, 0, window->width, window->height };
	}

	Viewport InitViewport(ui32t x, ui32t y, ui32t width, ui32t height)
	{
		return Viewport{ x, y, width, height };
	}

	Viewport* UpdateViewport(Viewport* viewport)
	{
		BM_CATCH(glViewport(viewport->x, viewport->y, viewport->width, viewport->height));

	}

	Status SetViewport(Viewport& v)
	{
		BM_CATCH(glViewport(v.x, v.y, v.width, v.height));
		return Status::Success;
	}

	Status SetViewportRaw(ui32t x, ui32t y, ui32t width, ui32t height)
	{
		BM_CATCH(glViewport(x, y, width, height));
		return Status::Success;
	}

	Status SetViewportIfDifferent(Viewport& v, ui32t x, ui32t y, ui32t width, ui32t height)
	{
		if (v.x != x || v.y != y || v.width != width || v.height != height)
		{
			v.x = x;
			v.y = y;
			v.width = width;
			v.height = height;
			SetViewport(v);
			return Status::Success;
		}
		return Status::Fail;
	}
}