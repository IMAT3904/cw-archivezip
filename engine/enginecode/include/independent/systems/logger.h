/** \file logger.h
*	\brief Logging class which is used to send all types of runtime information to the console.
*/
#pragma once

#include "system.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine {

	/** \class Logger
	*	\brief Logging class which is used to send all types of runtime information to the console.
	*/

	class Logger : public System {
	
	private:
		std::vector<spdlog::sink_ptr> sinks;	//!< vector of all the sinks that will be used in the logger 
		std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> consoleLog; //!< An std::out colored sink that will print out to the command line
		std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> fileLog; //!< A rotating file sink
		static std::shared_ptr<spdlog::logger> log; //!< reference to the logger
	
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;	//!< overridden start/init function
		void stop(SystemSignal close = SystemSignal::None, ...) override;	//!< overridden stop/close function
		inline static std::shared_ptr<spdlog::logger>& getLog() { return log; } //!< Accessor function
};
}

#define LOG_TRACE(...) ::Engine::Logger::getLog()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Engine::Logger::getLog()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Engine::Logger::getLog()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Engine::Logger::getLog()->error(__VA_ARGS__)
#define LOG_FATAL(...) ::Engine::Logger::getLog()->critical(__VA_ARGS__)

#define LOG_ASSERT(x, ...) {if(!(x)) {LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
