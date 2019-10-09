/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"
#include "systems/log.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{
	Engine::Log::initLog();

	auto application = Engine::startApplication();
	application->run();
	delete application;

	return 0;
}

