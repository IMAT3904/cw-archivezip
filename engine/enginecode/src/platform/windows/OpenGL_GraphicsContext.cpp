#include "engine_pch.h"
#include "include/platform/windows/OpenGL_GLFWGraphicsContext.h"

OpenGL_GLFWGraphicsContext::OpenGL_GLFWGraphicsContext(GLFWwindow * window) : m_window(window)
{
}

void OpenGL_GLFWGraphicsContext::init()
{
	glfwMakeContextCurrent(m_window);
	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	LOG_ASSERT(result, "{0}");
	LOG_WARN("GLAD Loaded");

	
	// Enable standard depth detest (Z-buffer)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	LOG_WARN("Z-Buffer Enabled");
	// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	LOG_WARN("CCW Enabled (Backface culling)");
}

void OpenGL_GLFWGraphicsContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}
