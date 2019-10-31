/** \file OpenGLVertexArray.h
*	\brief
*/
#pragma once
#include "rendering/vertexArray.h"

namespace Engine {

	class OpenGLVertexArray : public VertexArray
	{
		void bind() override;
		void unbind() override;
		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		std::shared_ptr<VertexBuffer> getVertexBuffer() ;
		std::shared_ptr<IndexBuffer> getIndexBuffer() ;
		unsigned int getDrawCount() ;

		static VertexArray * create();
	};

}
