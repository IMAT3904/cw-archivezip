/** \file system.h
*/

#pragma once

#include <cstdarg>

/**
\class Interface class for all systems
*/

namespace Engine {

	enum class SystemSignal { None = 0 };

	/**
	\class System 
	* Class for basic systems
	*/

	class System
	{
	public:
		virtual ~System() {};												//!< Constructor
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Stop the system
	};
}
