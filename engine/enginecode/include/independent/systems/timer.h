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
		std::chrono::high_resolution_clock::time_point startTimer;
		std::chrono::high_resolution_clock::time_point endTimer;
	public:
		void setStart() { startTimer = std::chrono::high_resolution_clock::now(); }
		void setEnd() { endTimer = std::chrono::high_resolution_clock::now(); }

		std::chrono::high_resolution_clock::time_point returnStart() { return startTimer; }
		std::chrono::high_resolution_clock::time_point returnEnd() { return endTimer; }

		std::chrono::duration<float> getSeconds() { return endTimer - startTimer; };
		std::chrono::duration<double, std::milli> getMilSec() { return endTimer - startTimer; };
		std::chrono::duration<float, std::micro> getMicSec() { return endTimer - startTimer; };

		


	};
}
