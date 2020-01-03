/** \file .h
*	\brief
*/

#pragma once
#include "renderCommand.h"
#include "uniformBuffers.h"
#include "buffers.h"
#include "material.h"
#include <map>
#include <memory>

namespace Engine {

	using SceneData = std::unordered_map<std::shared_ptr<UniformBuffer>, std::vector<void*>>;
	using PerDrawData = std::map<std::string, void*>;

	/**	\class
	*	\brief
	*/

	class Renderer
	{
	public:
		virtual void actionCommand(RenderCommand* command) = 0; //!< action a render command
		virtual void beginScene(const SceneData& sceneData) = 0; //!< prepare a scene for submission
		virtual void endScene() = 0; //!< end of a scene
		virtual void submit(const std::shared_ptr<Material> material) = 0; //!< submit a material
		virtual void flush() = 0; //!< draw everything

		static Renderer* createBasic3D();
		static Renderer* createBasicTextRenderer2D();
	};

}