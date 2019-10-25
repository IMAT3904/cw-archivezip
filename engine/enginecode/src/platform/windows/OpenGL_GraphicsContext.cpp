#include "engine_pch.h"
#include "include/platform/windows/OpenGL_GLFWGraphicsContext.h"

OpenGL_GLFWGraphicsContext::OpenGL_GLFWGraphicsContext(GLFWwindow * window) : m_window(window)
{
}

void OpenGL_GLFWGraphicsContext::init()
{
	glfwMakeContextCurrent(m_window);
	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	//assert
}

void OpenGL_GLFWGraphicsContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}
