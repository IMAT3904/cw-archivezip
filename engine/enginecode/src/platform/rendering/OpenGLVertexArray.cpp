/** \file OpenGLVertexArray.cpp
*	\brief
*/

#include "engine_pch.h"
#include "..\..\..\include\platform\rendering\OpenGLVertexArray.h"

namespace Engine {
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_renderer);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_renderer);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_renderer);
	}
	
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_renderer);
		vertexBuffer->bind();
		m_vertexBuffers.push_back(vertexBuffer);
	}
	
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_renderer);
		indexBuffer->bind();

		m_indexBuffer = indexBuffer;
	}

	unsigned int OpenGLVertexArray::getDrawCount() const
	{
		return 0;
	}
	
}