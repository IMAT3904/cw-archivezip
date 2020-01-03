#include "engine_pch.h"
#include "include/platform/GLFW/GLFWInputPoller.h"
#include "include/platform/GLFW/GLFWCodes.h"
#include "include/independent/core/application.h"

namespace Engine {
	
	bool GLFWInputPoller::isKeyPressedData(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetKey(window, keycode);
		return result == INPUT_PRESS || result == INPUT_REPEAT;
	}
	bool GLFWInputPoller::isMouseButtonPressedData(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetKey(window, button);
		return result == INPUT_PRESS;
	}
	glm::vec2 GLFWInputPoller::getMousePositionData()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float GLFWInputPoller::getMouseXData()
	{
		glm::vec2(x, y) = getMousePositionData();
		return x;
	}
	float GLFWInputPoller::getMouseYData()
	{
		glm::vec2(x, y) = getMousePositionData();
		return y;
	}
}