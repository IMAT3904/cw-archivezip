/** \file .h
*	\brief
*/

#pragma once
#include "bufferLayout.h"
#include <memory>


namespace Engine {

	/**	\class
	*	\brief
	*/
	class VertexBuffer {
	public:
		virtual void bind() = 0;	//!< Binds the buffer
		virtual void unbind() = 0;	//!< unbinds the buffer
		virtual void setLayout(VertexBufferLayout& layout) = 0;	//!< Sets the layout of the vertex buffer
		virtual const VertexBufferLayout& getLayout() const = 0; //!< Returns the layout of the vertex buffer
		virtual void edit(float* verticies, unsigned int size, unsigned int offset) = 0; //!<  edit the data stored inside the buffer
		
		static VertexBuffer * create(float* verticies, unsigned int size);	//!< returns an rendering api specific vertex buffer
	};

	/**	\class
	*	\brief
	*/
	class IndexBuffer {
	public:
		virtual void bind() = 0; //!< Binds the buffer
		virtual void unbind() = 0; //!< unbinds the buffer
		virtual unsigned int getCount() const = 0;	//!< Get the buffer count
		static IndexBuffer * create(unsigned int* indicies, unsigned int count); //!< returns an rendering api specific index buffer
	};



}