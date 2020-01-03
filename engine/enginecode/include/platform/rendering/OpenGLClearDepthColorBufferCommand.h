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

	class OpenGLClearDepthColorBufferCommand : public RenderCommand
	{
	private:

	public:
		OpenGLClearDepthColorBufferCommand() {};
		void action() override;
	};

	void OpenGLClearDepthColorBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
