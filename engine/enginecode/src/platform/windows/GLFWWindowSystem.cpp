#include "engine_pch.h"
#include "include/platform/windows/GLFWWindowSystem.h"


namespace Engine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char * description)
	{
		//LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void GLFWWindowSystem::start(SystemSignal init, ...)
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			LOG_ASSERT(success, "Assert failed: {0}");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
	}

	void GLFWWindowSystem::stop(SystemSignal close, ...)
	{
		glfwTerminate();
	}

	


}	