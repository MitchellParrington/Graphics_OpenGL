#pragma once
#include "bmpch.hpp"

namespace Bam
{
	struct Viewport;

	struct BM_API FrameBuffer
	{
		gluid frameBuffer;
		gluid colorBuffer;
		gluid depthStencilBuffer;
	};

	// NEW

	FrameBuffer* InitFrameBuffer(FrameBuffer* frameBuffer, Viewport* viewport);
	FrameBuffer InitFrameBuffer(Viewport* viewport);
	FrameBuffer* UpdateFrameBuffer(FrameBuffer* frameBuffer, Viewport* viewport);
	bool IsFrameBufferComplete(FrameBuffer* frameBuffer);
	void BindFrameBuffer(FrameBuffer* frameBuffer);
	void BindFrameBuffer(gluid frameBuffer);
	void DeleteFrameBuffer(FrameBuffer* frameBuffer);
	void DeleteFrameBuffer(gluid frameBuffer);

	// OLD

	Status BM_API InitFrameBuffer(FrameBuffer&, Viewport&);
	Status BM_API SetFrameBuffer(FrameBuffer&, Viewport&);
	Status BM_API CheckFrameBufferComplete(FrameBuffer&);
	Status BM_API BindFrameBuffer(FrameBuffer&);
	// Status BM_API BindFrameBuffer(ui32t);
	Status BM_API DeleteFrameBuffer(FrameBuffer&);
	// Status BM_API DeleteFrameBuffer(ui32t);
}