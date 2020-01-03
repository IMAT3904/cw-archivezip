/** \file OpenGLVertexBuffer.h
*	\brief
*/
#pragma once
#include "rendering/uniformBuffers.h"
#include "include/platform/OpenGL/OpenGLBuffers.h"

namespace Engine {

	/**	\class
	*	\brief
	*/
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		OpenGLUniformBuffer(unsigned int size, UniformBufferLayout & layout);
		OpenGLUniformBuffer(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout & layout);
		~OpenGLUniformBuffer();
		void bind() override; //!< Bind the buffer
		void unbind() override; //!< unbind the buffer
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) override; //!< Bind the buffer
		void setData(unsigned int offset, unsigned int size, void * data) override; //!< Bind the buffer
		UniformBufferLayout getLayout() const override; //!< Bind the buffer

	private:
		unsigned int m_objID;
		unsigned int m_bindingPoint;
		unsigned int m_uniformBufferIndex;

		UniformBufferLayout m_layout;

	};

}