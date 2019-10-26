#pragma once
#include "systems/WindowSystem.h"
#include "systems/logger.h"
#include "GLFW/glfw3.h"

namespace Engine {

	class GLFWWindowSystem : public WindowSystem
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
		std::shared_ptr<Logger> m_log;
	private:
		
	};

}
