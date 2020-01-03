/** \file OpenGLShader.h
*	\brief
*/

#pragma once
#include "windows/window.h"
#include "rendering/shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Engine {

	/**	\class OpenGLShader
	*	\brief 
	*/

	using GLLayout = std::map<std::string, std::string>;

	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~OpenGLShader();

		unsigned int id() override;
		void bind() override;
		void unbind() override;

		void uploadData(const std::string& name, void* data);
		void DispatchUniformUpload(ShaderDataType type, GLuint location, void* data);

	private:
		GLLayout glLayout;
		GLuint vertShader, fragShader;
		unsigned int shader_ID;
	};
}