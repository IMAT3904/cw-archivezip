/** \file .h
*	\brief
*/

#pragma once
#include "systems/logger.h"

namespace Engine {
	
	enum class ShaderDataType
	{
		None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool, Sampler2D
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		LOG_ASSERT(false, "Unknown ShaderDataType Size!");
		return 0;
	}

	static unsigned int ShaderDataTypeComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:	return 1;
		case ShaderDataType::Int2:	return 2;
		case ShaderDataType::Int3:	return 3;
		case ShaderDataType::Int4:	return 4;
		case ShaderDataType::Float:	return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat3:	return 3 * 3;
		case ShaderDataType::Mat4:	return 4*4;
		case ShaderDataType::Bool:	return 1;
		case ShaderDataType::Sampler2D:	return 1;
		}
		LOG_ASSERT(false, "Unknown ShaderDataType Component Count!");
		return 0;
	}


	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc)
	{
		ShaderDataType result = ShaderDataType::None;
		if (glslSrc == "bool") result = ShaderDataType::Bool;
		if (glslSrc == "int") result = ShaderDataType::Int;
		if (glslSrc == "ivec2") result = ShaderDataType::Int2;
		if (glslSrc == "ivec3") result = ShaderDataType::Int3;
		if (glslSrc == "ivec4") result = ShaderDataType::Int4;
		if (glslSrc == "float") result = ShaderDataType::Float;
		if (glslSrc == "vec2") result = ShaderDataType::Float2;
		if (glslSrc == "vec3") result = ShaderDataType::Float3;
		if (glslSrc == "vec4") result = ShaderDataType::Float4;
		if (glslSrc == "mat3") result = ShaderDataType::Mat3;
		if (glslSrc == "mat4") result = ShaderDataType::Mat4;
		if (glslSrc == "sampler2d") result = ShaderDataType::Sampler2D;
		return result;
	}


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

	class BufferLayout
	{
	public:
		BufferLayout() {};	//!< Default Constructor
		BufferLayout(const std::initializer_list<BufferElement>& elements); //!< Constructor which processes passed layout information
		inline unsigned int getStride() const { return m_stride; }	//!< Returns the stride of the layout
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
		void addElement(ShaderDataType dataType)
		{
			m_elements.push_back(BufferElement(dataType));
			calcStrideAndOffsets();
		}
	private:
		std::vector<BufferElement> m_elements;	//!< vector of buffer elements
		unsigned int m_stride;			//!< the stride (distance between the data lines) of the layout
		void calcStrideAndOffsets();	//!< function to calculate the stride distance and offset for each element in the layout
		
	};

	class VertexBuffer {
	public:
		virtual void bind() = 0;	//!< Binds the buffer
		virtual void unbind() = 0;	//!< unbinds the buffer
		virtual void edit(float* verticies, unsigned int size, unsigned int offset) = 0; //!<  edit the data stored inside the buffer
		virtual const BufferLayout& getLayout() const = 0;	//!< gets the buffer layout
		static VertexBuffer * create(float* verticies, unsigned int size);	//!< returns an rendering api specific vertex buffer
	};

	class IndexBuffer {
	public:
		virtual void bind() = 0; //!< Binds the buffer
		virtual void unbind() = 0; //!< unbinds the buffer
		virtual unsigned int getCount() const = 0;	//!< Get the buffer count
		static IndexBuffer * create(unsigned int* indicies, unsigned int count); //!< returns an rendering api specific index buffer
	};
}