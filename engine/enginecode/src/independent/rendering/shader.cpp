/** \file shader.cpp
*	\brief
*/

#include "engine_pch.h"
#include "rendering/shader.h"

#include "systems/logger.h"
#include "rendering/RenderAPI.h"
#include "../platform/rendering/OpenGLShader.h"

namespace Engine {

	Shader * Shader::create(const std::string & filepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			LOG_TRACE("OpenGLShader Loaded from filepath");
			return new OpenGLShader(filepath);
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
	Shader * Shader::create(const std::string & vertexFilepath, const std::string & fragmentFilepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			LOG_TRACE("OpenGLShaders Loaded from filepath");
			return new OpenGLShader(vertexFilepath, fragmentFilepath);
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