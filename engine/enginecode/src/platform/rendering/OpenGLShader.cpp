/** \file OpenGLShader.cpp
*	\brief
*/

#include "engine_pch.h"
#include "..\..\..\include\platform\rendering\OpenGLShader.h"
#include <string>
#include <fstream>

namespace Engine {

	OpenGLShader::OpenGLShader(const std::string & filepath)
	{
		std::fstream handle(filepath, std::ios::in);
		enum { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2 } region;
		if (!handle.is_open()) LOG_FATAL("Could not open shader file '{0}'", filepath);

		std::string line, src[2];

		while (getline(handle, line))
		{
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geometry") != std::string::npos) { region = NONE; continue; }
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; }

			if (region != NONE) src[region] += (line + "\n");
		}
		handle.close();

		vertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = src[VERTEX].c_str();
		glShaderSource(vertShader, 1, &source, 0);
		glCompileShader(vertShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Vertex Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(vertShader);
			return;
		}

		fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = src[FRAGMENT].c_str();
		glShaderSource(fragShader, 1, &source, 0);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Fragment Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(fragShader);
			glDeleteShader(vertShader);

			return;
		}

		shader_ID = glCreateProgram();
		glAttachShader(shader_ID, vertShader);
		glAttachShader(shader_ID, fragShader);
		glLinkProgram(shader_ID);

		GLuint isLinked = 0;
		glGetProgramiv(shader_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(shader_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(shader_ID, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Shader program linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(shader_ID);
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return;
		}

		
		glDetachShader(shader_ID, vertShader);
		glDetachShader(shader_ID, fragShader);
		
	}

	OpenGLShader::OpenGLShader(const std::string & vertexFilepath, const std::string & fragmentFilepath)
	{
		std::fstream handleVert(vertexFilepath, std::ios::in);
		if (!handleVert.is_open()) LOG_FATAL("Could not open vertex shader file '{0}'", vertexFilepath);
		std::string line, filesource;

		bool found = false;
		while (getline(handleVert, line))
		{
			if (line.find("#region Vertex") != std::string::npos) { found = true; continue; }
			if (found) filesource += (line + "\n");
		}
		handleVert.close();

		std::cout << filesource << std::endl;

		vertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = filesource.c_str();
		glShaderSource(vertShader, 1, &source, 0);
		glCompileShader(vertShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Vertex Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(vertShader);
			return;
		}

		std::fstream handleFrag(fragmentFilepath, std::ios::in);
		if (!handleFrag.is_open()) LOG_FATAL("Could not open fragment shader file '{0}'", fragmentFilepath);

		while (getline(handleFrag, line))
		{
			if (line.find("#region Fragment") != std::string::npos) { found = true; continue; }
			if (found) filesource += (line + "\n");
		}
		handleFrag.close();

		std::cout << filesource << std::endl;

		fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = filesource.c_str();
		glShaderSource(fragShader, 1, &source, 0);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Fragment Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(fragShader);
			glDeleteShader(vertShader);

			return;
		}

		shader_ID = glCreateProgram();
		glAttachShader(shader_ID, vertShader);
		glAttachShader(shader_ID, fragShader);
		glLinkProgram(shader_ID);

		GLuint isLinked = 0;
		glGetProgramiv(shader_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(shader_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(shader_ID, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Shader program linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(shader_ID);
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return;
		}


		glDetachShader(shader_ID, vertShader);
		glDetachShader(shader_ID, fragShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(shader_ID);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	unsigned int OpenGLShader::id()
	{
		return shader_ID;
	}

	void OpenGLShader::bind()
	{
		glUseProgram(shader_ID);
	}

	void OpenGLShader::unbind()
	{
		glUseProgram(0);
	}

	bool OpenGLShader::uploadData(const std::string & name, void * data)
	{
		
	}

	bool OpenGLShader::uploadData(const UniformLayout & uniforms)
	{
		return false;
	}

	BufferLayout OpenGLShader::getBufferLayout() const
	{
		return BufferLayout();
	}

	UniformLayout OpenGLShader::getUniformLayout() const
	{
		return UniformLayout();
	}

	void OpenGLShader::uploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(shader_ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}



}