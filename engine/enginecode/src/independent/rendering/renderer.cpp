/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/platform/rendering/OpenGLBasicRenderer.h"
#include "include/platform/rendering/OpenGLBasicTextRenderer.h"
#include "rendering/RenderAPI.h"
#include "systems/logger.h"


namespace Engine {

	Renderer * Renderer::createBasic3D()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			LOG_TRACE("OpenGL Basic Renderer Loaded");
			return new OpenGLBasicRenderer();
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

	Renderer * Renderer::createBasicTextRenderer2D()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_FATAL("Lack of API not supported.");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			LOG_TRACE("OpenGL Basic Text Renderer Loaded");
			return new OpenGLBasicTextRenderer();
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