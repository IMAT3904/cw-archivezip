/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "rendering/RenderAPI.h"
#include "rendering/buffers.h"
#include "../platform/rendering/OpenGLBuffers.h"
#include "systems/logger.h"

namespace Engine {
	
	IndexBuffer* IndexBuffer::create(unsigned int* indices, unsigned int size)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
			LOG_TRACE("OpenGL Index Buffer Init");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
		}
	}
	
}