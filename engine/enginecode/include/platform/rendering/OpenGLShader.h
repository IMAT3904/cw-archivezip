/** \file OpenGLShader.h
*	\brief
*/

#pragma once
#include "windows/window.h"
#include "rendering/shader.h"

#include <glad/glad.h>

namespace Engine {

	/**	\class OpenGLShader
	*	\brief 
	*/

	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~OpenGLShader();

		unsigned int id() override;
		void bind() override;
		void unbind() override;

		void uploadMat4(const std::string& name, glm::mat4* data);


	private:
		GLuint vertShader, fragShader;
		unsigned int program;
	};
}
