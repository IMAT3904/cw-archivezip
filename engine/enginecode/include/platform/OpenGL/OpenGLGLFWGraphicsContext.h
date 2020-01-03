/** \file OpenGL_GLFWGraphicsContext.h
*	\brief This header includes the graphics context for an OpenGL and GLFW window.
*/
#pragma once
#include "include/independent/windows/graphicsContext.h"
#include "include/independent/systems/logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


/**	\class OpenGL_GLFWGraphicsContext
*	\brief The OpenGL+GLFW graphics context implementation, that initializes GLAD and swaps 
*	the windows buffers.
*/
class OpenGL_GLFWGraphicsContext : public GraphicsContext
{
public:
	OpenGL_GLFWGraphicsContext(GLFWwindow* window);
	void init() override;
	void swapBuffers() override;
private:
	GLFWwindow* m_window;
	std::shared_ptr<Engine::Logger> m_log;
};
