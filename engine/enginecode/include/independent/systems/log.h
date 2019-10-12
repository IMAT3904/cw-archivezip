#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
	
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> l_Main;
		static std::shared_ptr<spdlog::logger> l_App; 
		static bool logRunning;
	public:
		static void initLog();
		static void endLog();

		static bool logStatus();
		static void log(const std::string& msg);
	
		inline static std::shared_ptr<spdlog::logger>& logMain() { return l_Main; }
		inline static std::shared_ptr<spdlog::logger>& logApp() { return l_App; }
	
	};
}
#define EG_MAIN_ERROR(...) ::Engine::Log::logMain()->error(__VA_ARGS__)
#define EG_MAIN_WARN(...) ::Engine::Log::logMain()->warn(__VA_ARGS__)
#define EG_MAIN_INFO(...) ::Engine::Log::logMain()->info(__VA_ARGS__)
#define EG_MAIN_TRACE(...) ::Engine::Log::logMain()->trace(__VA_ARGS__)
#define EG_MAIN_FATAL(...) ::Engine::Log::logMain()->fatal(__VA_ARGS__)

#define EG_APP_ERROR(...) ::Engine::Log::logApp()->error(__VA_ARGS__)
#define EG_APP_WARN(...) ::Engine::Log::logApp()->warn(__VA_ARGS__)
#define EG_APP_INFO(...) ::Engine::Log::logApp()->info(__VA_ARGS__)
#define EG_APP_TRACE(...) ::Engine::Log::logApp()->trace(__VA_ARGS__)
#define EG_APP_FATAL(...) ::Engine::Log::logApp()->fatal(__VA_ARGS__)

