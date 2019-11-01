/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "rendering/buffers.h"
#include "..\..\..\include\platform\rendering\OpenGLBuffers.h"
#include <glad/glad.h>

namespace Engine {
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float * verticies, unsigned int size, BufferLayout & layout)
	{
		glCreateBuffers(1, &m_renderer);
		glBindBuffer(GL_ARRAY_BUFFER, m_renderer);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
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
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indicies, GL_STATIC_DRAW);
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