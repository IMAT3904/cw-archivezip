/** \file vertexArray.h
*	\brief
*/

#pragma once
#include "buffers.h"

namespace Engine {
	
	class VertexArray 
	{
	public:
		static VertexArray * create();	//!< returns an API specific VertexArray
		virtual void bind() const = 0;	//!< Binds the vertex array
		virtual void unbind() const = 0; //!< unbinds the vertex array
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;	//!< Adds a vertex buffer
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;	//!< sets the index buffer for all vertex buffer
		virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffer() const = 0;	//!< gets the vertex buffers
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;	//!< gets the index buffer
		virtual unsigned int getDrawCount() const = 0;	//!< returns the number of triangles to be drawn
	};
}