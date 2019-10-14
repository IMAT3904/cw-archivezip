/** \file logger.h
*/
#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine {

	/**
	\class Logger
	...
	*/

	class Logger {
	private:
		static std::shared_ptr<spdlog::logger> log;
	public:
		static void initLog(std::string logName);
		inline static std::shared_ptr<spdlog::logger>& getLog() { return log; }
};
}
