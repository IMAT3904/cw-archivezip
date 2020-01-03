/** \file OpenGLRenderCommands.h
*	\brief
*/

#pragma once
#include "rendering/renderCommand.h"
#include "glad/glad.h"

namespace Engine {

	/**	\class
	*	\brief
	*/

	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
		void action() override;
	};



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

	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_g, m_a);
	}

	void OpenGLClearDepthColorBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void OpenGLSetDepthTestLessCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
	}

	void OpenGLSetBackFaceCullingCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

	}


	

}
