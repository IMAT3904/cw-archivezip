/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
	#include "include/platform/windows/GLFWWindowSystem.h"
#endif //NG_PLATFORM_WINDOWS

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_log->initLog("Application");		//Start our logger
		LOG_WARN(m_log, "Log Initialized");
		
		m_timer->startFrame();				//Start our frame counter
		LOG_WARN(m_log, "Frame Counter Started");

		// Start windows system
#ifdef NG_PLATFORM_WINDOWS	
		m_windowsSystem = std::shared_ptr<WindowSystem>(new GLFWWindowSystem());
		LOG_WARN(m_log, "GLFW Window System Started");
#endif
		m_windowsSystem->start();
		LOG_WARN(m_log, "Window System Started");
		m_window = std::unique_ptr<Window>(Window::create());
		LOG_WARN(m_log, "Window Created");
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
		LOG_WARN(m_log, "Window Event Callback Set");

	}

	Application::~Application()
	{
		//stop log
		//stop timer
		m_windowsSystem->stop();
	}

	void Application::run()
	{
		m_running = true;		//start run/frame/event loop
		while (m_running) {		//while the application is running
															
			m_window->onUpdate();									//frame
			frameDuration = m_timer->FrameDuration();				//calculate frame duration
			LOG_TRACE(m_log, "FPS:{0}.", (int)(1.0f / frameDuration));	//convert into and show fps
			
		}
	}

	void Application::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onClose));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(onResize));
		dispatcher.dispatch<WindowLostFocus>(BIND_EVENT_FN(onLostFocus));
		dispatcher.dispatch<WindowMoved>(BIND_EVENT_FN(onWinMoved));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(onKeyPressed));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(onKeyReleased));
		dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT_FN(onKeyTyped));
		dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FN(onMbPressed));
		dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FN(onMbReleased));
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(onMouseMoved));
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(onMouseScrolled));
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		LOG_INFO(m_log, "Closing Application");
		m_running = false;
		return true;
	}

	bool Application::onResize(WindowResizeEvent & e)
	{
		LOG_INFO(m_log, "Window Resized to {0}x{1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onLostFocus(WindowLostFocus & e)
	{
		LOG_INFO(m_log, "Window lost focus at {0} , {1}", e.getXPos(), e.getYPos());
		return true;
	}

	bool Application::onWinMoved(WindowMoved & e)
	{
		LOG_INFO(m_log, "Window moved!");
		return true;
	}

	bool Application::onKeyPressed(KeyPressedEvent & e)
	{
		LOG_INFO(m_log, "Key Pressed: {0}, R#:{1}", e.getKeyCode(), e.getRepeatCount());
		return true;
	}

	bool Application::onKeyReleased(KeyReleasedEvent & e)
	{
		LOG_INFO(m_log, "Key Released: {0}", e.getKeyCode());
		return true;
	}

	bool Application::onKeyTyped(KeyTypedEvent & e)
	{
		LOG_INFO(m_log, "Key Typed: {0}", e.getKeyCode());
		return true;
	}

	bool Application::onMbPressed(MouseButtonPressed & e)
	{
		LOG_INFO(m_log, "Mouse button pressed: {0}", e.getButton());
		return true;
	}

	bool Application::onMbReleased(MouseButtonReleased & e)
	{
		LOG_INFO(m_log, "Mouse button released: {0}", e.getButton());
		return true;
	}

	bool Application::onMouseMoved(MouseMovedEvent & e)
	{
		LOG_INFO(m_log, "Mouse moved at: {0},{1}", e.getXPos(), e.getYPos());
		return true;
	}

	bool Application::onMouseScrolled(MouseScrolledEvent & e)
	{
		LOG_INFO(m_log, "Mouse scrolled at: {0},{1}", e.getXPos(), e.getYPos());
		return true;
	}

}


