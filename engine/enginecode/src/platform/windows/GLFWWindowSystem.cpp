#include "engine_pch.h"
#include "include/platform/windows/GLFWWindowSystem.h"
#include "windows/window.h"
#include "include/platform/windows/WindowsWindow.h"


namespace Engine {

	static bool s_GLFWInitialized = false;

	void GLFWWindowSystem::start(SystemSignal init, ...)
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			//assert once you have fixed loger
			s_GLFWInitialized = true;
		}
	}

	void GLFWWindowSystem::stop(SystemSignal close, ...)
	{
		
		glfwTerminate();
	}

}	