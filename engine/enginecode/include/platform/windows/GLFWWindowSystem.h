#pragma once
#include "systems/WindowSystem.h"

namespace Engine {

	class GLFWWindowSystem : public WindowSystem
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
		//static void GLFWErrorCallback(int error, const char* description);
	};

}
