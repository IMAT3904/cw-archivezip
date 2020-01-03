/** \file .h
*	\brief
*/

#pragma once
#include "rendering/shaderDataType.h"


namespace Engine {

	/**	\class
	*	\brief
	*/
	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;

		BufferElement() {};	//!< Default Constructor
		BufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {};
		//!< Constructor which processes passed element information
	};


}