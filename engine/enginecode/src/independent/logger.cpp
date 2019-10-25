/** \file logger.cpp
*/
#include "engine_pch.h"
#include "systems\logger.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Logger::log;

	void Logger::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		log = spdlog::stdout_color_mt("Engine");
		log->set_level(spdlog::level::trace);
	}

	void Logger::stop(SystemSignal close, ...)
	{
		log.reset();
	}

}