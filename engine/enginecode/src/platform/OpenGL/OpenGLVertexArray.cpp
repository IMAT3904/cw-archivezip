/** \file OpenGLVertexArray.cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_objID);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_objID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_objID);
	}
	
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_objID);
		vertexBuffer->bind();
		m_vertexBuffers.push_back(vertexBuffer);
	}
	
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_objID);
		indexBuffer->bind();
		m_indexBuffer = indexBuffer;
	}

	unsigned int OpenGLVertexArray::getDrawCount() const
	{
		return 0;
	}
	
}