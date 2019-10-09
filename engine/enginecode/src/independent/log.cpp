#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {
	
	void Engine::Log::initLog()
	{
		m_logger->set_level(spdlog::level::trace);
		m_logger = spdlog::stdout_color_mt("Console");
		m_logger->set_pattern("%^[%T] %n: %v%$");
	}
}