/** \file .h
*	\brief
*/

#pragma once
#include "rendering/renderer.h"
#include "rendering/material.h"
#include "glad/glad.h"
#include <memory>

namespace Engine {

	/**	\class
	*	\brief
	*/

	class OpenGLBasicTextRenderer : public Renderer
	{
	public:

		void actionCommand(RenderCommand* command) override;
		void beginScene(const SceneData& sceneData) override; 
		void endScene() override; 
		void submit(const std::shared_ptr<Material> material) override; 
		void flush() override;

	};

}