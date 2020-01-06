/** \file shader.h
*	\brief
*/
#pragma once
#include <map>
#include <glm/glm.hpp>
#include "rendering/buffers.h"

using UniformLayout = std::map<std::string, void*>;

namespace Engine {

	class Shader
	{
	public:
		virtual unsigned int id() = 0; //!< Get the API id of the shader programme
		virtual void bind() = 0;	//!< Bind the shader
		virtual void unbind() = 0;	//!< Unbind the shader
		
		virtual void uploadData(const std::string& name, void* data) = 0;

		//virtual VertexBufferLayout getBufferLayout() const = 0;
		//virtual VertexBufferLayout getBufferLayout() const = 0;

		static Shader* create(const std::string& filepath); //!< Create, compile and link API specific shade from single source file
		static Shader* create(const std::string& vertexFilepath, const std::string& fragmentFilepath); //!< Create, compile and link API specific shade from single source file
	
	
	private:
		UniformLayout uniformLayout; //< Layout for uniforms
	};
	

}
