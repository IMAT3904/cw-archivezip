/** \file OpenGLVertexBuffer.h
*	\brief
*/
#pragma once
#include "rendering/buffers.h"

namespace Engine {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, unsigned int size, BufferLayout& layout);
		void bind() override;
		void unbind() override;
		void edit(float* verticies, unsigned int size, unsigned int offset) override;
		
		const BufferLayout& getLayout() const override;
	private:
		unsigned int m_renderer;
		BufferLayout m_layout;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indicies, unsigned int count);
		void bind() override;
		void unbind() override;
		unsigned int getCount() const override;
		
	private:
		unsigned int m_count;
		unsigned int m_renderer;
	};

};