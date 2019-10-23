/** \file timer.h
*/
#pragma once
#include <chrono>

namespace Engine {
	
	/**
	\class Timer
	* 
	*/

	class Timer
	{
	private:
		static std::chrono::high_resolution_clock::time_point frameStart, frameEnd; //!< Time points used to save time points - used to calculate time
		static std::chrono::duration<float> frameTime;	//!< Duration that will hold our calculated time
	public:
		static void startFrame();		//!< Init function
		static float FrameDuration();	//!<
	};

}

