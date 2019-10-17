/** \file timer.cpp
*/

#include "engine_pch.h"
#include "systems/timer.h"


namespace Engine {
	
	std::chrono::high_resolution_clock::time_point Timer::frameStart;	
	std::chrono::high_resolution_clock::time_point Timer::frameEnd;
	std::chrono::duration<float> Timer::frameTime;

	void Timer::startFrame()
	{
		frameStart = std::chrono::high_resolution_clock::now();		//starts the frame timer
	}
	float Timer::FrameDuration()
	{
		frameEnd = std::chrono::high_resolution_clock::now();		//frame timer ends
		frameTime = frameEnd - frameStart;							//calculate duration
		frameStart = std::chrono::high_resolution_clock::now();		 //reset timer
		return frameTime.count();									//return the duration
	}
}

