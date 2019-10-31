/** \file event.h
*	\brief An agnostic and abstract implementation of a window system
*/
#pragma once
#include "system.h"

namespace Engine {

	/** \class WindowSystem
	*	\brief An agnostic and abstract implementation of a window system, it is just a system.
	*/
	class WindowSystem : public System
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) = 0;
		void stop(SystemSignal close = SystemSignal::None, ...) = 0;
	};	

}