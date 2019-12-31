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

		program = glCreateProgram();
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		GLuint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Shader program linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(program);
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return;
		}

		
		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
		
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

		program = glCreateProgram();
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		GLuint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			LOG_ERROR("Shader program linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(program);
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return;
		}


		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
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

	


}