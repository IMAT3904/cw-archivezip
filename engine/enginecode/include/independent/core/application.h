/** \file application.h
*	\brief Fundemental class of the engine. A singleton which runs the game loop infinitely.
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
#include "rendering/buffers.h"
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"


namespace Engine {

	/**	\class Application
	*	\brief Fundemental class of the engine. A singleton which runs the game loop infinitely.
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
		
		//! Reference to our flat color vertex array
		std::shared_ptr<VertexArray> m_vertexArrayFC;

		//! Reference to our textured phong vertex array
		std::shared_ptr<VertexArray> m_vertexArrayTP;

		std::shared_ptr<Texture> m_FCTex;
		std::shared_ptr<Texture> m_TPTex;

		std::shared_ptr<Shader> m_FCShader;
		std::shared_ptr<Shader> m_TPShader;

#pragma region TempVars
		// Temp stuff
		//unsigned int m_FCvertexArray; // Flat Colour VAO
		//unsigned int m_FCvertexBuffer;// Flat Colour VBO
		//unsigned int m_TPvertexArray; // Textured Phong VAO
		//unsigned int m_TPvertexBuffer;// Textured Phong VBO
		//unsigned int m_FCindexBuffer; // Index buffer for colour cube
		//unsigned int m_TPindexBuffer; // Index buffer for texture Phong cube
		unsigned int m_FCprogram; // Flat colour shader ID
		unsigned int m_TPprogram; // Textured Phong shader ID
		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?
#pragma endregion TempVars

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
		bool onWinMoved(WindowMovedEvent& e); 
		
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