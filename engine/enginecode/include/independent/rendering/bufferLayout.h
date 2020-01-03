#pragma once

/** \file .h
*	\brief
*/

#pragma once
#include "bufferElement.h"

namespace Engine {

	/**	\class
	*	\brief
	*/
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() {};	//!< Default Constructor
		VertexBufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements) //!< Constructor which processes passed layout information
		{
			calcStrideAndOffsets();
		}

		inline unsigned int getStride() const { return m_stride; }	//!< Returns the stride of the layout
		inline const std::vector<BufferElement>& getElements() const { return m_elements; }
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
		void calcStrideAndOffsets() //!< function to calculate the stride distance and offset for each element in the layout
		{
			int offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
				m_stride += element.m_size;
			}
		}
	};

	/**	\class
	*	\brief
	*/
	class UniformBufferLayout
	{
	public:
		UniformBufferLayout() {};	//!< Default Constructor
		UniformBufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements) //!< Constructor which processes passed layout information
		{
			calcStrideAndOffsets();
		}

		inline unsigned int getStride() const { return m_stride; }	//!< Returns the stride of the layout
		inline const std::vector<BufferElement>& getElements() const { return m_elements; }

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
		void calcStrideAndOffsets()	//!< function to calculate the stride distance and offset for each element in the layout
		{
			unsigned int offset = 0;
			m_stride = 0;

			for (auto& element : m_elements)
			{
				element.m_offset = offset;
				offset += element.m_size;

				for (int i = offset; !(offset % 16 == 0); i++)
				{
					offset = i;
				}

				m_stride = offset;
			}
		}
	};
}
