/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"
#include "math.h"


namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		appLog->initLog("Application");		//Start our logger
		LOG_WARN(appLog, "Log Initialized");
		appTimer->startFrame();				//Start our frame counter
		LOG_WARN(appLog, "Frame Counter Started");
		if (s_instance == nullptr)			
		{
			s_instance = this;
			
		}
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		m_running = true;		//start run/frame/event loop
		float runTime = 0.f;	//how long the run time of the loop has been
		while (m_running) {		//while the application is running
															
															//frame
															
	
			frameDuration = appTimer->FrameDuration();									//calculate frame duration
			runTime += frameDuration;													//accumulate our runtime
			LOG_TRACE(appLog,"#:{0}. FPS:{1}.", (int)runTime, (int)(1.0f / frameDuration));	//convert into and show fps
			if (runTime > 10.f)							//if run time has been longer than 10s
			{
				WindowResizeEvent e1(1024, 720);
				onEvent(e1);
				WindowCloseEvent e2;
				onEvent(e2);
				WindowLostFocus e3(4.f,2.f);
				onEvent(e3);
				WindowMoved e4;
				onEvent(e4);
				KeyPressed e5(1,0);
				onEvent(e5); 
				KeyReleased e6(5);
				onEvent(e6);
				KeyTyped e7(6);
				onEvent(e7);
				MouseButtonPressed e8(19);
				onEvent(e8);
				MouseButtonReleased e9(20);
				onEvent(e9);
				MouseMoved e10(10.f,2.f);
				onEvent(e10);
				MouseScrolled e11(2.f, 7.f);
				onEvent(e11);
				LOG_FATAL(appLog, "Completed Runtime Loop");
			}
		}
	}

	void Application::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMoved>(std::bind(&Application::onWinMoved, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleased>(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<KeyTyped>(std::bind(&Application::onKeyTyped, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&Application::onMbPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&Application::onMbReleased, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMoved>(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolled>(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		LOG_INFO(appLog, "Closing Application");
		m_running = false;
		return true;
	}

	bool Application::onResize(WindowResizeEvent & e)
	{
		LOG_INFO(appLog, "Window Resized to {0}x{1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onLostFocus(WindowLostFocus & e)
	{
		LOG_INFO(appLog, "Window lost focus at {0} , {1}", e.getXPos(), e.getYPos());
		return true;
	}

	bool Application::onWinMoved(WindowMoved & e)
	{
		LOG_INFO(appLog, "Window moved!");
		return true;
	}

	bool Application::onKeyPressed(KeyPressed & e)
	{
		LOG_INFO(appLog, "Key Pressed: {0}, R#:{1}", e.getKeyCode(), e.getRepeatCount());
		return true;
	}

	bool Application::onKeyReleased(KeyReleased & e)
	{
		LOG_INFO(appLog, "Key Released: {0}", e.getKeyCode());
		return true;
	}

	bool Application::onKeyTyped(KeyTyped & e)
	{
		LOG_INFO(appLog, "Key Typed: {0}", e.getKeyCode());
		return true;
	}

	bool Application::onMbPressed(MouseButtonPressed & e)
	{
		LOG_INFO(appLog, "Mouse button pressed: {0}", e.getButton());
		return true;
	}

	bool Application::onMbReleased(MouseButtonReleased & e)
	{
		LOG_INFO(appLog, "Mouse button released: {0}", e.getButton());
		return true;
	}

	bool Application::onMouseMoved(MouseMoved & e)
	{
		LOG_INFO(appLog, "Mouse moved at: {0},{1}", e.getXPos(), e.getYPos());
		return true;
	}

	bool Application::onMouseScrolled(MouseScrolled & e)
	{
		LOG_INFO(appLog, "Mouse scrolled at: {0},{1}", e.getXPos(), e.getYPos());
		return true;
	}

}


