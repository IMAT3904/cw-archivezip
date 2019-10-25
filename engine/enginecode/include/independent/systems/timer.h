
/** \file timer.h
*/

#pragma once
#include <chrono>
#include "system.h"

namespace Engine {
	
	/**
	\class Timer
	* 
	*/

	class Timer : public System
	{
	private:
		static std::chrono::high_resolution_clock::time_point frameStart, frameEnd; //!< Time points used to save time points - used to calculate time
		static std::chrono::duration<float> frameTime;	//!< Duration that will hold our calculated time
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
		static float frameDuration();	//!<
	};

}



