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
		static std::shared_ptr<spdlog::logger>& getLog() { return log; }
};
}

#define LOG_WARN(log, ...) log->getLog()->warn(__VA_ARGS__)
#define LOG_INFO(log , ...) log->getLog()->info(__VA_ARGS__)
#define LOG_TRACE(log , ...) log->getLog()->trace(__VA_ARGS__)
#define LOG_ERROR(log , ...) log->getLog()->error(__VA_ARGS__)
#define LOG_FATAL(log , ...) log->getLog()->critical(__VA_ARGS__)
