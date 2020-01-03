/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "../platform/rendering/OpenGLBasicRenderer.h"

namespace Engine {

	void OpenGLBasicRenderer::actionCommand(RenderCommand * command)
	{
		command->action();
		delete command;
	}
	void OpenGLBasicRenderer::beginScene(const SceneData & sceneData)
	{
		for (auto uboPair : sceneData)
		{
			unsigned int offset = 0;
			unsigned int size;
			int i = 0;

			UniformBufferLayout layout = uboPair.first->getLayout();

			for (auto bufferElement : layout)
			{
				uboPair.first->setData(bufferElement.m_offset, bufferElement.m_size, uboPair.second[i]);
				i++;
			}
		}
	}
	void OpenGLBasicRenderer::endScene()
	{
	}
	void OpenGLBasicRenderer::submit(const std::shared_ptr<Material> material)
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
		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);

	}
	void OpenGLBasicRenderer::flush()
	{
	}
}