/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "rendering/material.h"
#include "rendering/RenderAPI.h"
#include "../platform/rendering/OpenGLMaterial.h"
#include "systems/logger.h"

namespace Engine {
	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			LOG_TRACE("OpenGLMaterial Loaded from filepath");
			return new OpenGLMaterial();
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			return nullptr;
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			return nullptr;
			break;
		}
	}

	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VBO)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			LOG_TRACE("OpenGLMaterial Loaded from filepath");
			return new OpenGLMaterial();
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			return nullptr;
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			return nullptr;
			break;
		}
	}
}