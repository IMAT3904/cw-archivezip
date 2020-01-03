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

	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
		void action() override;
	};

	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_g, m_a);
	}

}