#pragma once
#include "system.h"

namespace Engine {

	class WindowSystem : public System
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) = 0;
		void stop(SystemSignal close = SystemSignal::None, ...) = 0;
	};	

}