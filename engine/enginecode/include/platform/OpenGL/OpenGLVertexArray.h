/** \file OpenGLVertexArray.h
*	\brief
*/
#pragma once
#include "rendering/vertexArray.h"
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

	class OpenGLVertexArray : public VertexArray
	{
	public:
		
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void bind() const override;
		void unbind() const override;
		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() const override { return m_vertexBuffers; };
		std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return m_indexBuffer; };
		unsigned int getDrawCount() const override;

	private:
		unsigned int m_objID;
		unsigned int m_vertexBufferIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};

}
