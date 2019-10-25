/** \file logger.cpp
*/
#include "engine_pch.h"
#include "systems\logger.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Logger::log; //!< static variable init

	void Logger::start(SystemSignal init, ...)
	{
		consoleLog = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();	//Set console log to be a stdout colored sink
		fileLog = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("../debug/logs/log.txt", 1048576 * 5, 5);  //!< Set our file sink which has a max file size of 5MB and 5 rotated files.
		sinks.push_back(consoleLog); //!< Push the sinks to the vector
		sinks.push_back(fileLog); //!< Push the sinks to the vector
		log = std::make_shared<spdlog::logger>("Engine", begin(sinks), end(sinks)); //!< Compile all of our sinks to the logger
		sinks.clear();		//!< clear the vector as it is no longer used
		consoleLog.reset();	//!< clear up the shared pointed as it is no longer used
		fileLog.reset();	//!< clear up the shared pointed as it is no longer used
		log->sinks()[0]->set_level(spdlog::level::trace); //!< setting the level the logger
		log->sinks()[1]->set_level(spdlog::level::trace); //!< setting the level the logger
		log->sinks()[0]->set_pattern("%^[%T.%e] %n: [%l]: %v %$"); //!< 24hour + ms clock with the name of the log and log output along with its type
		log->sinks()[1]->set_pattern("%+"); //!< spdlog default format
		log->info(">>>>>----=== New Application ===----<<<<<");	//!< Print out a header to signal a new run of the application
	}

	void Logger::stop(SystemSignal close, ...)
	{
		spdlog::drop_all(); //!< removes all logs from the registry
		log.reset(); //!< clearing up our shared pointer
	}

}