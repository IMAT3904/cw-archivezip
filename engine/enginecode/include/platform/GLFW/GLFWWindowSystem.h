/** \file GFLWWindowSystem.h
*	\brief This header includes our GLFW Windows System
*/
#pragma once
#include "systems/WindowSystem.h"
#include "systems/logger.h"
#include "GLFW/glfw3.h"

namespace Engine {

	/**	\class GLFWWindowSystem
	*	\brief Initializes GLFW for the creation of a glfw window.
	*/
	class GLFWWindowSystem : public WindowSystem
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
	private:
		std::shared_ptr<Logger> m_log;
	};

}
