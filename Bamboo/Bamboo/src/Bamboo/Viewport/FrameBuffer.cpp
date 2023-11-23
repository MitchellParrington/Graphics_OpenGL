#include "bmpch.hpp"
#include "FrameBuffer.hpp"

#include "Vendor/Glad.hpp"

#include "Viewport.hpp"

namespace Bam
{
	// NEW


	FrameBuffer* InitFrameBuffer(FrameBuffer* frameBuffer, Viewport* viewport)
	{
		BM_CATCH(glGenFramebuffers(1, &frameBuffer->frameBuffer));
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->frameBuffer)); // bind framebuffer

		BM_CATCH(glGenTextures(1, &frameBuffer->colorBuffer));
		BM_CATCH(glBindTexture(GL_TEXTURE_2D, frameBuffer->colorBuffer));
		BM_CATCH(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, viewport->width, viewport->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		BM_CATCH(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		BM_CATCH(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		BM_CATCH(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBuffer->colorBuffer, 0));

		BM_CATCH(glGenTextures(1, &frameBuffer->depthStencilBuffer));
		BM_CATCH(glBindTexture(GL_TEXTURE_2D, frameBuffer->depthStencilBuffer));
		BM_CATCH(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, viewport->width, viewport->height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
		BM_CATCH(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, frameBuffer->depthStencilBuffer, 0));

		ui32t frameBuffer_status = BM_CATCH(glCheckFramebufferStatus(GL_FRAMEBUFFER));
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		if (frameBuffer_status != GL_FRAMEBUFFER_COMPLETE)
		{
			BM_CORE_LOG_ERROR("Frame Buffer not complete");
		}
		return frameBuffer;
	}

	FrameBuffer InitFrameBuffer(Viewport* viewport)
	{
		FrameBuffer frameBuffer;
		InitFrameBuffer(&frameBuffer, viewport);
		return frameBuffer;
	}

	FrameBuffer* UpdateFrameBuffer(FrameBuffer* frameBuffer, Viewport* viewport)
	{
		InitFrameBuffer(frameBuffer, viewport);
		return frameBuffer;
	}

	bool IsFrameBufferComplete(FrameBuffer* frameBuffer)
	{
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->frameBuffer));
		ui32t framebuffer_status = BM_CATCH(glCheckFramebufferStatus(GL_FRAMEBUFFER));
		if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
		{
			BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			return false;
		}
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		return true;
	}

	void BindFrameBuffer(FrameBuffer* frameBuffer)
	{
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->frameBuffer));
	}

	void BindFrameBufferR(gluid frameBuffer)
	{
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer));
	}

	void DeleteFrameBuffer(FrameBuffer* frameBuffer)
	{
		BM_CATCH(glDeleteFramebuffers(1, &frameBuffer->frameBuffer));
	}

	void DeleteFrameBuffer(gluid frameBuffer)
	{
		BM_CATCH(glDeleteFramebuffers(1, &frameBuffer));
	}

	// OLD

	Status InitFrameBuffer(FrameBuffer& f, Viewport& v)
	{
		BM_CATCH(glGenFramebuffers(1, &f.frameBuffer));
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, f.frameBuffer)); // bind framebuffer

		BM_CATCH(glGenTextures(1, &f.colorBuffer));
		BM_CATCH(glBindTexture(GL_TEXTURE_2D, f.colorBuffer));
		BM_CATCH(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, v.width, v.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		BM_CATCH(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		BM_CATCH(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		BM_CATCH(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, f.colorBuffer, 0));

		BM_CATCH(glGenTextures(1, &f.depthStencilBuffer));
		BM_CATCH(glBindTexture(GL_TEXTURE_2D, f.depthStencilBuffer));
		BM_CATCH(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, v.width, v.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
		BM_CATCH(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, f.depthStencilBuffer, 0));

		ui32t framebuffer_st = BM_CATCH(glCheckFramebufferStatus(GL_FRAMEBUFFER));
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		if (framebuffer_st != GL_FRAMEBUFFER_COMPLETE)
		{
			BM_CORE_LOG_ERROR("Frame Buffer not complete");
			return Status::Fail;
		}
		return Status::Success;
	}

	Status SetFrameBuffer(FrameBuffer& f, Viewport& v)
	{
		BM_CATCH(glGenFramebuffers(1, &f.frameBuffer));
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, f.frameBuffer)); // bind framebuffer

		BM_CATCH(glGenTextures(1, &f.colorBuffer));
		BM_CATCH(glBindTexture(GL_TEXTURE_2D, f.colorBuffer));
		BM_CATCH(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, v.width, v.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		BM_CATCH(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		BM_CATCH(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		BM_CATCH(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, f.colorBuffer, 0));

		BM_CATCH(glGenTextures(1, &f.depthStencilBuffer));
		BM_CATCH(glBindTexture(GL_TEXTURE_2D, f.depthStencilBuffer));
		BM_CATCH(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, v.width, v.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
		BM_CATCH(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, f.depthStencilBuffer, 0));

		ui32t framebuffer_st = BM_CATCH(glCheckFramebufferStatus(GL_FRAMEBUFFER));
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		if (framebuffer_st != GL_FRAMEBUFFER_COMPLETE)
		{
			BM_CORE_LOG_ERROR("Frame Buffer not complete");
			return Status::Fail;
		}
		return Status::Success;
	}

	Status CheckFrameBufferComplete(FrameBuffer& f)
	{
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, f.frameBuffer));
		ui32t framebuffer_st = BM_CATCH(glCheckFramebufferStatus(GL_FRAMEBUFFER));
		if (framebuffer_st != GL_FRAMEBUFFER_COMPLETE)
		{
			BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			return Status::Fail;
		}
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		return Status::Success;
	}

	Status BindFrameBuffer(FrameBuffer& f)
	{
		BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, f.frameBuffer));
		return Status::Success;
	}

	// Redefinition
	//Status BindFrameBuffer(ui32t f)
	//{
	//	BM_CATCH(glBindFramebuffer(GL_FRAMEBUFFER, f));
	//	return Status::Success;
	//}

	Status DeleteFrameBuffer(FrameBuffer& f)
	{
		BM_CATCH(glDeleteFramebuffers(1, &f.frameBuffer));
		return Status::Success;
	}
	
	// Redefinition
	//Status DeleteFrameBuffer(ui32t f)
	//{
	//	BM_CATCH(glDeleteFramebuffers(1, &f));
	//	return Status::Success;
	//}
}