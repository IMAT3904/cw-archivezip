#pragma once
#include "include/independent/windows/graphicsContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class OpenGL_GLFWGraphicsContext : public GraphicsContext
{
private:
	GLFWwindow* m_window;
public:
	OpenGL_GLFWGraphicsContext(GLFWwindow* window);
	void init() override;
	void swapBuffers() override;
};
