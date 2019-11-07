/** \file vertexArray.cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/independent/rendering/vertexArray.h"

#include "systems/logger.h"
#include "rendering/RenderAPI.h"
#include "../platform/rendering/OpenGLVertexArray.h"



namespace Engine {


	VertexArray * VertexArray::create()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:    
			LOG_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
			break;
		case RenderAPI::API::OpenGL:  
			return new OpenGLVertexArray();
			break;
		}
		LOG_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}