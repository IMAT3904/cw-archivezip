/** \file texture.cpp
*	\brief
*/

#include "engine_pch.h"
#include "rendering/texture.h"

#include "systems/logger.h"
#include "rendering/RenderAPI.h"
#include "../platform/rendering/OpenGLTexture.h"

namespace Engine {
	Texture * Texture::createFromFile(const std::string & filepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);
			LOG_TRACE("OpenGLTexture Loaded from Filepath");
			break;
		case RenderAPI::API::Direct3D:
			LOG_FATAL("Direct3D not yet supported");
			break;
		default:
			LOG_FATAL("Unknown Graphics API");
			break;
		}
	}
	Texture * Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(width, height, channels, texData);
			LOG_TRACE("OpenGLTexture Loaded from raw data");
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