/** \file logger.cpp
*/
#include "engine_pch.h"
#include "systems\logger.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Logger::log;

	void Engine::Logger::initLog(std::string logName)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		log = spdlog::stdout_color_mt(logName);
		log->set_level(spdlog::level::trace);
	}

}