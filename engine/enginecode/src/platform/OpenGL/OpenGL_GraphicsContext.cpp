#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLGLFWGraphicsContext.h"

OpenGL_GLFWGraphicsContext::OpenGL_GLFWGraphicsContext(GLFWwindow * window) : m_window(window)
{
}

void OpenGL_GLFWGraphicsContext::init()
{
	glfwMakeContextCurrent(m_window);
	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	LOG_ASSERT(result, "{0}");
	LOG_WARN("GLAD Loaded");
}

void OpenGL_GLFWGraphicsContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}
