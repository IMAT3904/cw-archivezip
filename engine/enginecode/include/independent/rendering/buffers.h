/** \file .h
*	\brief
*/

#pragma once
#include "systems/logger.h"
#include <cstdint>

namespace Engine {
	
	enum class ShaderDataType
	{
		None = 0, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, Bool, Sampler2D
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
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


	class BufferElement {
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;

		BufferElement() {};
		BufferElement(ShaderDataType dataType, bool normalized = false) : m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalized(normalized) {};
	};

	class BufferLayout
	{
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements)
		{
			calcStrideAndOffsets();
		}
		
		inline unsigned int getStride() const { return m_stride; }
		void addElement(ShaderDataType dataType)
		{
			m_elements.push_back(BufferElement(dataType));
			calcStrideAndOffsets();
		}

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
		
	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride;
		void calcStrideAndOffsets() 
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
				m_stride += element.m_size;
			}
		}
	};

	class VertexBuffer {
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void edit(float* verticies, unsigned int size, unsigned int offset) = 0;
		virtual const BufferLayout& getLayout() const = 0;

		static VertexBuffer * create(float* verticies, unsigned int size, BufferLayout& layout);
	};

	class IndexBuffer {
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		
		virtual unsigned int getCount() const = 0;
		static IndexBuffer * create(unsigned int* indicies, unsigned int count);
	};
}