/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"


namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		appLog->initLog("Application");
		appLog->getLog()->warn("Application Log Initialized!");
		if (s_instance == nullptr)
		{
			s_instance = this;
			
		}
	}

	Application::~Application()
	{
		appLog.reset();
	}

	

	void Application::run()
	{
		
	}

}
