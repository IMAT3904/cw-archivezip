#pragma once
#include "system.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
	
	class Log : public System
	{
	private:
		static std::shared_ptr<spdlog::logger> m_logger;
	public:
		static void initLog();		
	};
}

