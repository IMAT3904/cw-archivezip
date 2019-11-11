/** \file OpenGLVertexBuffer.h
*	\brief
*/
#pragma once
#include "rendering/buffers.h"

namespace Engine {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, unsigned int size);
		~OpenGLVertexBuffer();
		void bind() override;
		void unbind() override;
		void setLayout(BufferLayout& layout) override;
		const BufferLayout& getLayout() const override { return m_layout; }
		void edit(float* verticies, unsigned int size, unsigned int offset) override;
	private:
		unsigned int m_vertexBufferIndex;
		unsigned int m_renderer;
		BufferLayout m_layout;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indicies, unsigned int count);
		~OpenGLIndexBuffer();
		void bind() override;
		void unbind() override;
		unsigned int getCount() const override;
		
	private:
		unsigned int m_renderer;
		unsigned int m_count;
		
	};

};