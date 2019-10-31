/** \file .h
*	\brief
*/

#pragma once
#include "buffers.h"

namespace Engine {
	
	class VertexArray 
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;
		virtual unsigned int getDrawCount() const = 0;
		
		static VertexArray * create();
	};
}