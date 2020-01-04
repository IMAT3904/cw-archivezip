/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include <memory>
#include "include/platform/OpenGL/OpenGLMaterial.h"

namespace Engine {

	OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		setShader(shader);
		setGeometry(VAO);
	}

	OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO)
	{
		setShader(shader);
		setGeometry(VBO);
	}

	void OpenGLMaterial::setShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader = shader;
	}
	void OpenGLMaterial::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{
		bool isVA = std::holds_alternative<std::shared_ptr<VertexArray>>(geometry);
		if (isVA)
		{
			m_geometry = std::get <std::shared_ptr<VertexArray>>(geometry);
		}
	}
	void OpenGLMaterial::setDataBlock(const std::map<std::string, void*>& data)
	{
		m_data = data;
	}
	void OpenGLMaterial::setDataElement(const std::string & dataName, void * data)
	{
		m_data[dataName] = data;
	}
}