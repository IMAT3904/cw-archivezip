/** \file application.h
*/
#pragma once

#include "math.h"

#include "systems/WindowSystem.h"
#include "windows/window.h"
#include "systems/logger.h"
#include "systems/timer.h"
#include "events/event.h"
#include "events/windowEvents.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"


namespace Engine {

	/**
	\class Application
	* Fundemental class of the engine. A singleton which runs the game loop infinitely.
	*/

	class Application
	{
	protected:
		//! Constructor
		Application(); 

	private:
		//! Singleton instance of the application
		static Application* s_instance; 

		//! Bool to control the running/event loop
		bool m_running = false;	

		//! Float which holds how long a frame takes
		float frameDuration = 0.f;

		//! Reference to our window
		std::shared_ptr<Window> m_window;

		//! Reference to our log
		std::shared_ptr<Logger> m_log;

		//! Reference to our timer
		std::shared_ptr<Timer> m_timer;

		//! Reference to our windows system
		std::shared_ptr<WindowSystem> m_windowsSystem;


	public:
		//! Deconstructor
		virtual ~Application(); 

		//! Instance getter from singleton pattern
		inline static Application& getInstance() { return *s_instance; } 

		//! Gets our window
		inline std::shared_ptr<Window> getWindow() { return m_window; }
		
		//! Main loop
		void run(); 
		
		//! Event call function
		/*!
		\param e The event that we pass through
		*/
		void onEvent(Event& e);
		
		//! On close event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onClose(WindowCloseEvent& e);
		
		//! On resize event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onResize(WindowResizeEvent& e);
		
		//! On lost focus event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onLostFocus(WindowLostFocus& e);
		
		//! On window moved event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onWinMoved(WindowMoved& e); 
		
		//! On key pressed event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onKeyPressed(KeyPressedEvent& e); 
		
		//! On key released event
		/*!
		 \param e The event that we pass through
		\return a Bool based on if it has been handled or not
		*/
		bool onKeyReleased(KeyReleasedEvent& e);
		
		//! On Key typed event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onKeyTyped(KeyTypedEvent& e); 
		
		//! On mouse button pressed event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onMbPressed(MouseButtonPressed& e);
		
		//! On mouse button released event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onMbReleased(MouseButtonReleased& e);
		
		//! On mouse moved event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onMouseMoved(MouseMovedEvent& e);
		
		//! On mouse scrolled event
		/*!
		 \param e The event that we pass through
		\return a bool based on if it has been handled or not
		*/
		bool onMouseScrolled(MouseScrolledEvent& e);
	};

	//! Function definition which provides an entry hook
	Application* startApplication(); 

}