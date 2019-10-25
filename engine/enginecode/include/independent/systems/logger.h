/** \file logger.h
*/
#pragma once

#include "system.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine {

	/**
	\class Logger
	* Logging class which is used to send all types of runtime information to the console.
	*/

	class Logger : public System {
	
	private:
		static std::shared_ptr<spdlog::logger> log; //!< reference to our logger
	
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;

		static std::shared_ptr<spdlog::logger>& getLog() { return log; } //!< Accessor function
};
}

#define LOG_WARN(...) m_log->getLog()->warn(__VA_ARGS__)
#define LOG_INFO(...) m_log->getLog()->info(__VA_ARGS__)
#define LOG_TRACE(...) m_log->getLog()->trace(__VA_ARGS__)
#define LOG_ERROR(...) m_log->getLog()->error(__VA_ARGS__)
#define LOG_FATAL(...) m_log->getLog()->critical(__VA_ARGS__)

#define LOG_ASSERT(x, ...) {if(!(x)) {LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
