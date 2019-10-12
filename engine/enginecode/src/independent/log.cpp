#include "engine_pch.h"
#include "systems/log.h"

namespace Engine {
	
	std::shared_ptr<spdlog::logger> Log::l_Main;
	std::shared_ptr<spdlog::logger> Log::l_App;
	bool Log::logRunning;

	void Log::initLog()
	{
		logRunning = true;
		spdlog::set_pattern("%^[%T] %n: %v%$");
		l_Main = spdlog::stdout_color_mt("Console");
		l_Main->set_level(spdlog::level::trace);

		l_App = spdlog::stdout_color_mt("Application");
		l_App->set_level(spdlog::level::trace);
		
	}
	void Log::endLog()
	{
		l_Main.reset();
	}
	bool Log::logStatus()
	{
		if (l_Main != nullptr)
		{
			return true;
		}
		else {
			return false;
		}
	}
	void Log::log(const std::string & msg)
	{
		l_Main->info(msg);
	}
}