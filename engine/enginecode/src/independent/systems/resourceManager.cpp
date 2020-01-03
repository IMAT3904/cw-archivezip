/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "..\..\..\include\independent\systems\resourceManager.h"

namespace Engine {
	
	AssetManager<IndexBuffer> ResourceManager::m_indexBuffers;
	AssetManager<Shader> ResourceManager::m_shaders;
	AssetManager<Texture> ResourceManager::m_textures;
	AssetManager<VertexArray> ResourceManager::m_VAOs;
	AssetManager<VertexBuffer> ResourceManager::m_VBOs;

	std::shared_ptr<IndexBuffer> ResourceManager::addIndexBuffer(const std::string & name, unsigned int * indices, unsigned int count)
	{
		std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::create(indices, count));
		m_indexBuffers.add(name, indexBuffer);
		return indexBuffer;
	}

	std::shared_ptr<Shader> ResourceManager::addShader(const std::string & filepath)
	{
		std::shared_ptr<Shader> shader(Shader::create(filepath));
		m_shaders.add(filepath, shader);
		return shader;
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & filepath)
	{
		std::shared_ptr<Texture> texture(Texture::createFromFile(filepath));
		m_textures.add(filepath, texture);
		return texture;
	}

	std::shared_ptr<VertexArray> ResourceManager::addVAO(const std::string & name)
	{
		std::shared_ptr<VertexArray> vao(VertexArray::create());
		vao->bind();
		m_VAOs.add(name, vao);
		return vao;
	}	

	std::shared_ptr<VertexBuffer> ResourceManager::addVBO(const std::string & name, float * vertices, unsigned int size, VertexBufferLayout & layout)
	{
		std::shared_ptr<VertexBuffer> vbo(VertexBuffer::create(vertices, size));
		vbo->setLayout(layout);
		m_VBOs.add(name, vbo);
		return vbo;
	}
}