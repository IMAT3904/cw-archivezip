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
		enum { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2} region;
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
			LOG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

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
			LOG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return;
		}

		program = glCreateProgram();
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			//glDeleteProgram(program);
			//glDeleteShader(vertShader);
			//glDeleteShader(fragShader);

			return;
		}

		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);



		/*
		for(int x = 0; x < 2; x++)
		{
			if (x == 0)
			{
				shader[x] = glCreateShader(GL_VERTEX_SHADER);
			}
			else
			{
				shader[x] = glCreateShader(GL_FRAGMENT_SHADER);
			}
			const GLchar* source = src[x].c_str();
			glShaderSource(shader[x], 1, &source, 0);
			glCompileShader(shader[x]);

			GLint isCompiled = 0;
			glGetShaderiv(shader[x], GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader[x], GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader[x], maxLength, &maxLength, &infoLog[0]);
				LOG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

				glDeleteShader(shader[x]);
				continue;
			}

		}
		
		program = glCreateProgram();
		for (int x = 0; x < 2; x++) 
		{
			glAttachShader(program, shader[x]);
		}
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(program);
			for (int x = 0; x < 2; x++)
			{
				glDeleteShader(shader[x]);
			}

			return;
		}
		for (int x = 0; x < 2; x++)
		{
			glDetachShader(program, shader[x]);
		} */

	}

	OpenGLShader::OpenGLShader(const std::string & vertexFilepath, const std::string & fragmentFilepath)
	{
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(program);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	unsigned int OpenGLShader::id()
	{
		return program;
	}

	void OpenGLShader::bind()
	{
		glUseProgram(program);
	}

	void OpenGLShader::unbind()
	{
		glUseProgram(0);
	}

	bool OpenGLShader::uploadData(const std::string & name, void * data)
	{
		return false;
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

}