/** \file system.h
*	\brief Interface class for all systems
*/
#pragma once
#include <cstdarg>

namespace Engine {
	
	//! Enum class defining SystemSignal types
	enum class SystemSignal { None = 0 };

	/** \class System 
	*	\brief Interface class for all systems
	*/

	class System
	{
	public:
		virtual ~System() {};												//!< Constructor
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Stop the system
	};
}
