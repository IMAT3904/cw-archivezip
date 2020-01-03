/** \file .h
*	\brief
*/

#pragma once
#include "systems/logger.h"
#include "bufferLayout.h"
#include "shader.h"
#include <memory>


namespace Engine {
	
	/**	\class
	*	\brief
	*/
	class UniformBuffer {
	public:
		virtual void bind() = 0; //!< Bind the buffer
		virtual void unbind() = 0; //!< unbind the buffer
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) = 0; //!< Bind the buffer
		virtual void setData(unsigned int offset, unsigned int size, void * data) = 0; //!< Bind the buffer
		virtual UniformBufferLayout getLayout() const = 0; //!< Bind the buffer

		static UniformBuffer * create(unsigned int size, UniformBufferLayout& layout);
		static UniformBuffer * create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout);
	};

}