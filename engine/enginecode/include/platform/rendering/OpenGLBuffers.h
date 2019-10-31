/** \file OpenGLVertexBuffer.h
*	\brief
*/
#pragma once
#include "rendering/buffers.h"

namespace Engine {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void bind() override;
		void unbind() override;
		void edit(float* verticies, unsigned int size, unsigned int offset) override;
		
		const BufferLayout& getLayout() ;
		VertexBuffer * create(float* verticies, unsigned int size, BufferLayout& layout);
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
		void bind() override;
		void unbind() override;

		virtual unsigned int getCount();
		static IndexBuffer * create(unsigned int* indicies, unsigned int count);
	};

};