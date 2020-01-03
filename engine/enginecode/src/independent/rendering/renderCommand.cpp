/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "systems/logger.h"
#include "include/platform/OpenGL/OpenGLRenderCommands.h"
#include "rendering/RenderAPI.h"
#include "rendering/renderCommand.h"

namespace Engine {

	RenderCommand * RenderCommand::ClearDepthColorBufferCommand()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLClearDepthColorBufferCommand();
			break;
		}
	}

	RenderCommand * RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetClearColourCommand(r, g, b, a);
			break;
		}
	}

	RenderCommand * RenderCommand::setDepthTestLessCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetDepthTestLessCommand(enabled);
			break;
		}
	}

	RenderCommand * RenderCommand::setBackfaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			LOG_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetBackFaceCullingCommand(enabled);
			break;
		}
	}

}