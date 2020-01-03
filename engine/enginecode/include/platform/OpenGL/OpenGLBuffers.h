/** \file OpenGLVertexBuffer.h
*	\brief
*/
#pragma once
#include "rendering/buffers.h"
#include "include/platform/OpenGL/OpenGLBuffers.h"

namespace Engine {


	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, unsigned int size);
		~OpenGLVertexBuffer();
		void bind() override;
		void unbind() override;
		void setLayout(VertexBufferLayout& layout) override;
		const VertexBufferLayout& getLayout() const override { return m_layout; }
		void edit(float* verticies, unsigned int size, unsigned int offset) override;
	private:
		unsigned int m_vertexBufferIndex;
		unsigned int m_objID;
		VertexBufferLayout m_layout;
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
		unsigned int m_objID;
		unsigned int m_count;
		
	};


};