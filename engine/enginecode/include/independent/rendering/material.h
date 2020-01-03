/** \file .h
*	\brief
*/

#pragma once
#include <memory>
#include <map>
#include <variant>
#include "rendering/material.h"
#include "shader.h"
#include "vertexArray.h"
#include "uniformBuffers.h"

namespace Engine {

	/**	\class
	*	\brief
	*/
	class Material
	{
	public:
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0; //!< Set the shader
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0; //!<)
		virtual void setDataBlock(const std::map<std::string, void *>& data) = 0; //!< Set a block of data as the per draw data
		virtual void setDataElement(const std::string& dataName, void * data) = 0; //!< set a single uniform
		virtual void setMaterial(const std::string& dataName, const std::shared_ptr<Shader>& shader, void * data) = 0; //!< set a material
		//virtual void setVertexData(float * vertices, unsigned int size, unsigned int offset) = 0; //!< Set the geometry directly

		virtual std::shared_ptr<Shader> getShader() = 0; //!< Get the shader
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0; //!< Get the geometry
		virtual std::map<std::string, void *> getData() = 0; //!< Get the per draw data

		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO); //!< Create a VAO
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO); //!< Create a VBO
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<UniformBuffer>& UBO); //!< Create a UBO

	};
}