/** \file shader.h
*	\brief
*/
#pragma once
#include <map>
#include "rendering/buffers.h"

using UniformLayout = std::map<std::string, void*>;

namespace Engine {

	class Shader
	{
	public:
		virtual unsigned int id() = 0; //!< Get the API id of the shader programme
		virtual void bind() = 0;	//!< Bind the shader
		virtual void unbind() = 0;	//!< Unbind the shader
		virtual bool uploadData(const std::string& name, void * data) = 0; //!< Upload data of any type to the gpu
		virtual bool uploadData(const UniformLayout& uniforms) = 0;	//!< Upload data of any type to the GPU
		virtual BufferLayout getBufferLayout() const = 0; //!< Get the buffer layout for the shader
		virtual UniformLayout getUniformLayout() const = 0; //!< Get the structure of the data which can be uploaded

		 static Shader* create(const std::string& filepath); //!< Create, compile and link API specific shade from single source file
		 static Shader* create(const std::string& vertexFilepath, const std::string& fragmentFilepath); //!< Create, compile and link API specific shade from single source file

	};
	

}
