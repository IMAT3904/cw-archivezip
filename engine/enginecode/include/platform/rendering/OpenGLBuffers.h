/** \file OpenGLVertexBuffer.h
*	\brief
*/
#pragma once
#include "rendering/buffers.h"

namespace Engine {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, unsigned int size);
		~OpenGLVertexBuffer();
		void bind() override;
		void unbind() override;
		void setLayout(VertexBufferLayout& layout) override;
		const VertexBufferLayout& getLayout() const override { return m_layout; }
		void edit(float* verticies, unsigned int size, unsigned int offset) override;
	private:
		unsigned int m_vertexBufferIndex;
		unsigned int m_objID;
		VertexBufferLayout m_layout;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indicies, unsigned int count);
		~OpenGLIndexBuffer();
		void bind() override;
		void unbind() override;
		unsigned int getCount() const override;
		
	private:
		unsigned int m_objID;
		unsigned int m_count;
		
	};

	/**	\class
	*	\brief
	*/
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		OpenGLUniformBuffer(unsigned int size);
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

	};


};