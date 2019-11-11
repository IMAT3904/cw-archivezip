/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "..\..\..\include\platform\rendering\OpenGLBuffers.h"
#include <glad/glad.h>

namespace Engine {
	
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:	return GL_INT;
		case ShaderDataType::Int2:	return GL_INT;
		case ShaderDataType::Int3:	return GL_INT;
		case ShaderDataType::Int4:	return GL_INT;
		case ShaderDataType::Float:	return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:	return GL_FLOAT;
		case ShaderDataType::Mat4:	return GL_FLOAT;
		case ShaderDataType::Bool:	return	GL_BOOL;
		}
		LOG_ASSERT(false, "Unknown ShaderDataType To Open GL Type!");
		return 0;
	}
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float * verticies, unsigned int size, BufferLayout& layout) : m_layout(layout)
	{
		glCreateBuffers(1, &m_renderer);
		glBindBuffer(GL_ARRAY_BUFFER, m_renderer);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
		
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_vertexBufferIndex);
			glVertexAttribPointer(m_vertexBufferIndex,
				ShaderDataTypeComponentCount(element.m_dataType),
				ShaderDataTypeToOpenGLType(element.m_dataType),
				element.m_normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.m_offset);
			m_vertexBufferIndex++;
		}

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		//clear up vertex buffers
	}

	void OpenGLVertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_renderer);
	}

	void OpenGLVertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::edit(float * verticies, unsigned int size, unsigned int offset)
	{

	}

	const BufferLayout & OpenGLVertexBuffer::getLayout() const
	{
		return m_layout;
	}
	
	


	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int * indicies, unsigned int count) : m_count(count)
	{
		glCreateBuffers(1, &m_renderer);
		glBindBuffer(GL_ARRAY_BUFFER, m_renderer);
		glBufferData(GL_ARRAY_BUFFER, count, indicies, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		//clear up index buffers
	}

	void OpenGLIndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer);
	}

	void OpenGLIndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int OpenGLIndexBuffer::getCount() const
	{
		return m_count;
	}
	
	

}