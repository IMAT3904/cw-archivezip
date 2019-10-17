/** \file entryPoint.h
* Our entry point to the program which runs our main loop. 
*/
#pragma once

#include "core/application.h"

extern Engine::Application* Engine::startApplication(); //!< Include our application class

int main(int argc, char** argv)
{
	auto application = Engine::startApplication(); //!< Initiate our instance
	application->run();								//!< Run our main loop
	delete application;								//!< Clean up by deleting our instance
	return 0;										
}

