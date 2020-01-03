/** \file .cpp
*	\brief
*/

#include "engine_pch.h"

#include "include/platform/OpenGL/OpenGLUniformBuffers.h"
#include "systems/logger.h"
#include "rendering/RenderAPI.h"
#include "rendering/uniformBuffers.h"


namespace Engine {


	UniformBuffer * UniformBuffer::create(unsigned int size, UniformBufferLayout & layout)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer(size, layout);
			LOG_TRACE("OpenGL Uniform Buffer Init");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			return nullptr;
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			return nullptr;
			break;
		}
	}

	UniformBuffer * UniformBuffer::create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout & layout)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLUniformBuffer(size, rangeStart, rangeEnd, layout);
			LOG_TRACE("OpenGL Uniform Buffer Init");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			return nullptr;
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			return nullptr;
			break;
		}
	}
}