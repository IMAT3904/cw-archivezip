/** \file .h
*	\brief
*/

#pragma once
#include "rendering/renderCommand.h"

#include "glad/glad.h"

namespace Engine {

	/**	\class
	*	\brief
	*/

	class OpenGLSetBackFaceCullingCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGLSetBackFaceCullingCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};

	void OpenGLSetBackFaceCullingCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

	}

}
