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

	class OpenGLSetDepthTestLessCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGLSetDepthTestLessCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};

	void OpenGLSetDepthTestLessCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
	}

}

