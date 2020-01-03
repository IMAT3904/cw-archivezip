/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/platform/rendering/OpenGLBasicTextRenderer.h"

namespace Engine {

	void OpenGLBasicTextRenderer::actionCommand(RenderCommand * command)
	{
		command->action();
		delete command;
	}

	void OpenGLBasicTextRenderer::submit(const std::shared_ptr<Material> material)
	{
		//Bind the shader
		auto shader = material->getShader();
		shader->bind();

		//Bind the geometry
		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->bind();

		//Set each uniform in the data
		auto uniformData = material->getData();
		for (auto dataPair : uniformData)
		{
			shader->uploadData(dataPair.first, dataPair.second);
		}

		//Issue a draw call
		glDrawElements(GL_QUADS, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLBasicTextRenderer::beginScene(const SceneData & sceneData)
	{
	}

	void OpenGLBasicTextRenderer::endScene()
	{
	}

	

	void OpenGLBasicTextRenderer::flush()
	{
	}
}