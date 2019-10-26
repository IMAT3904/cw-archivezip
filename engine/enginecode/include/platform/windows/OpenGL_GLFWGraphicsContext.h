#pragma once
#include "include/independent/windows/graphicsContext.h"
#include "include/independent/systems/logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
