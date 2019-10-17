/** \file timer.h
*/
#pragma once
#include <chrono>

namespace Engine {
	
	/**
	\class Timer
	...
	*/

	class Timer
	{
	private:
		static std::chrono::high_resolution_clock::time_point frameStart, frameEnd;
		static std::chrono::duration<float> frameTime;
	public:
		static void startFrame();
		static float FrameDuration();
	};

}

