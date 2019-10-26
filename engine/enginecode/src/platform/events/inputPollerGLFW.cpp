#include "engine_pch.h"
#include "..\..\..\include\platform\events\inputPollerGLFW.h"


namespace Engine {
	
	bool inputPollerGLFW::isKeyPressedData(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetKey(window, keycode);
		return result == INPUT_PRESS || result == INPUT_REPEAT;
	}
	bool inputPollerGLFW::isMouseButtonPressedData(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetKey(window, button);
		return result == INPUT_PRESS;
	}
	glm::vec2 inputPollerGLFW::getMousePositionData()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float inputPollerGLFW::getMouseXData()
	{
		glm::vec2(x, y) = getMousePositionData();
		return x;
	}
	float inputPollerGLFW::getMouseYData()
	{
		glm::vec2(x, y) = getMousePositionData();
		return y;
	}
}