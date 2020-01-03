/** \file .cpp
*	\brief
*/

#include "engine_pch.h"

#include "include/platform/OpenGL/OpenGLBuffers.h"
#include "systems/logger.h"
#include "rendering/RenderAPI.h"
#include "rendering/buffers.h"


namespace Engine {
	


	VertexBuffer* VertexBuffer::create(float* verticies, unsigned int size)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(verticies, size);
			LOG_TRACE("OpenGL Vertex Buffer Init");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			break;
		}
	}

	IndexBuffer * IndexBuffer::create(unsigned int * indicies, unsigned int count)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indicies, count);
			LOG_TRACE("OpenGL Index Buffer Init");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			break;
		}
	}

}