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

	class OpenGLBasicRenderer : public Renderer
	{
	public:

		void actionCommand(RenderCommand* command) override; //!< action a render command
		void beginScene(const SceneData& sceneData) override; //!< prepare a scene for submission
		void endScene() override; //!< end of a scene
		void submit(const std::shared_ptr<Material> material) override; //!< submit a material
		void flush() override; //!< draw everything

	};

}