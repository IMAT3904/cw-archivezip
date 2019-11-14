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
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);
			LOG_TRACE("OpenGLShader Loaded from filepath");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			break;
		}
	}
	Shader * Shader::create(const std::string & vertexFilepath, const std::string & fragmentFilepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertPath, fragPath);
			LOG_TRACE("OpenGLShaders Loaded from filepath");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			break;
		}
	}
	

}