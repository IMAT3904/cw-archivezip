/** \file application.h
*/
#pragma once
#include "systems/logger.h"
#include "systems/timer.h"
#include "events/event.h"
#include "events/windowEvents.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = false;
		float frameDuration = 0.f;
	public:
		
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		void onEvent(Event& e);
		bool onClose(WindowCloseEvent& e); //!< On close event
		bool onResize(WindowResizeEvent& e); //!< On resize event
		bool onLostFocus(WindowLostFocus& e); //!< On lost focus event
		bool onWinMoved(WindowMoved& e); //!< On window moved event
		bool onKeyPressed(KeyPressed& e); //!< On key pressed event
		bool onKeyReleased(KeyReleased& e); //!< On key released event
		bool onKeyTyped(KeyTyped& e); //!< On key released event
		bool onMbPressed(MouseButtonPressed& e); //!< On mouse button pressed event
		bool onMbReleased(MouseButtonReleased& e); //!< On mouse button released event
		bool onMouseMoved(MouseMoved& e); //!< On mouse moved event
		bool onMouseScrolled(MouseScrolled& e); //!< On mouse scrolled event

		std::shared_ptr<Engine::Logger> appLog;
		std::shared_ptr<Engine::Timer> appTimer;
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}