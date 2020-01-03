/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "../platform/rendering/OpenGLBuffers.h"

#include "systems/logger.h"
#include "rendering/RenderAPI.h"
#include "rendering/buffers.h"


namespace Engine {
	
	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements)
	{
		calcStrideAndOffsets();
	}

	void VertexBufferLayout::calcStrideAndOffsets()
	{
		int offset = 0;
		m_stride = 0;
		for (auto& element : m_elements)
		{
			element.m_offset = offset;
			offset += element.m_size;
			m_stride += element.m_size;
		}
	}

	UniformBufferLayout::UniformBufferLayout(const std::initializer_list<BufferElement>& elements)
	{
		calcStrideAndOffsets();
	}

	void UniformBufferLayout::calcStrideAndOffsets()
	{
		unsigned int offset = 0;
		m_stride = 0;

		for (auto& element : m_elements)
		{
			element.m_offset = offset;
			offset += element.m_size;

			for (int i = offset; !(offset % 16 == 0); i++)
			{
				offset = i;
			}

			m_stride = offset;
		}

	}

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
			break;
		}
	}

	
	UniformBuffer * UniformBuffer::create(unsigned int size, UniformBufferLayout & layout)
	{
		return nullptr;
	}

	UniformBuffer * UniformBuffer::create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout & layout)
	{
		return nullptr;
	}

}