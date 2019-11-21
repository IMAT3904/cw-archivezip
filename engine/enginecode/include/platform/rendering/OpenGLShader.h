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

	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		~OpenGLShader();

		unsigned int id() override;
		void bind() override;
		void unbind() override;
		bool uploadData(const std::string& name, void * data) override;
		bool uploadData(const UniformLayout& uniforms) override;
		BufferLayout getBufferLayout() const override;
		UniformLayout getUniformLayout() const override;

		void uploadUniformInt(const std::string& name, int value);
		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);


	private:
		
		GLuint vertShader, fragShader;
		unsigned int shader_ID;
	};
}