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

		std::string line, code[2], type, name;

		while (getline(handle, line))
		{
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geometry") != std::string::npos) { region = NONE; continue; }
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; }

			if (region != NONE) code[region] += (line + "\n");

			if (line._Starts_with("uniform"))
			{
				std::string uniformLine = line.substr(line.find(" ") + 1);
				type = uniformLine.substr(0, uniformLine.find(" "));
				name = uniformLine.substr(uniformLine.find(" ") + 1);
				name = name.substr(0, name.find(";"));

				glLayout[name] = type;
			}
		}

		vertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = code[VERTEX].c_str();
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

		source = code[FRAGMENT].c_str();
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
		std::string line, filesource, type, name;

		bool found = false;
		while (getline(handleVert, line))
		{
			if (line.find("#region Vertex") != std::string::npos) { found = true; continue; }
			if (found) filesource += (line + "\n");
			if (line._Starts_with("uniform"))
			{
				std::string uniformLine = line.substr(line.find(" ") + 1);
				type = uniformLine.substr(0, uniformLine.find(" "));
				name = uniformLine.substr(uniformLine.find(" ") + 1);
				name = name.substr(0, name.find(";"));

				glLayout[name] = type;
			}
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

	void OpenGLShader::uploadData(const std::string & name, void * data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		DispatchUniformUpload(GLSLStrToSDT(glLayout[name]), loc, data);
		uniformLayout[name] = data;

	}



	void OpenGLShader::DispatchUniformUpload(ShaderDataType type, GLuint location, void * data)
	{
		const float * addrf;
		const int * addri;
		GLfloat valueFloat;
		GLint valueInt;
		
	    switch (type)
		{
				
			case ShaderDataType::Float:
				valueFloat = *(float*)data;
				glUniform1f(location, valueFloat);
				break;
			case ShaderDataType::Float2:
				addrf = (const float*)data;
				glUniform2fv(location, 1, addrf);
				break;
			case ShaderDataType::Float3:
				valueFloat = *(float*)data;
				glUniform3f(location, 1, 1, valueFloat);
				break;
			case ShaderDataType::Mat4:
				addrf = (const float*)data;
				glUniformMatrix4fv(location, 1, GL_FALSE, addrf);
				break;
			case ShaderDataType::Int:
				valueInt = *(int*)data;
				glUniform1i(location, valueInt);
				break;
			case ShaderDataType::Int2:
				addri = (const int *)data;
				glUniform2iv(location, 1, addri);
				break;
			case ShaderDataType::Int3:
				addri = (const int *)data;
				glUniform3iv(location, 1, addri);
				break;
			case ShaderDataType::Int4:
				addri = (const int *)data;
				glUniform4iv(location, 1, addri);
				break;
			case ShaderDataType::Bool:
				valueInt = *(bool*)data;
				glUniform1i(location, valueInt);
				break;
			defualt:
				LOG_ERROR("Shader data type not supported.");
				break;
		}
	}
	
}