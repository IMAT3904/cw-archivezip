/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLUniformBuffers.h"
#include <glad/glad.h>

namespace Engine {

	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int size, UniformBufferLayout & layout)
	{
		glGenBuffers(1, &m_objID);
		glBindBuffer(GL_UNIFORM_BUFFER, m_objID);
		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPoint, m_objID, 0, size);

	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout & layout)
	{

	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		//clear up uniform buffers
	}

	void OpenGLUniformBuffer::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_objID);
	}

	void OpenGLUniformBuffer::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string & blockName)
	{
		m_uniformBufferIndex = glGetUniformBlockIndex(shader->id(), blockName.c_str());
		glUniformBlockBinding(shader->id(), m_uniformBufferIndex, m_bindingPoint);
	}

	void OpenGLUniformBuffer::setData(unsigned int offset, unsigned int size, void * data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_objID);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	}

	UniformBufferLayout OpenGLUniformBuffer::getLayout() const
	{
		return UniformBufferLayout();
	}

}