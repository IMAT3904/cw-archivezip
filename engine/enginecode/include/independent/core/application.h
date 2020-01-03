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
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"
#include "systems/resourceManager.h"
#include "rendering/material.h"
#include "rendering/renderer.h"

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
		
		std::shared_ptr<Window> m_window; //!< Reference to our window		
		std::shared_ptr<ResourceManager> m_resources; //!< Resource manager
		std::shared_ptr<Timer> m_timer; //!< Timing system
		std::shared_ptr<WindowSystem> m_windowsSystem; //!< Windows System
		std::shared_ptr<Logger> m_log; //!< Logging System
		
		//! Reference to our flat color vertex array
		std::shared_ptr<VertexArray> m_FCVAO;
		std::shared_ptr<VertexArray> m_TPVAO;

		//! Reference to our flat cube and textured phong textures
		std::shared_ptr<Texture> m_FCTex;
		std::shared_ptr<Texture> m_TPTex;

		//! Reference to our flat cube and textured phong shaders
		std::shared_ptr<Shader> m_FCShader;
		std::shared_ptr<Shader> m_TPShader;

		std::shared_ptr<UniformBuffer> m_UBOMatrices;
		std::shared_ptr<UniformBuffer> m_UBOLights;

		std::shared_ptr<Material> m_FCCube;
		std::shared_ptr<Material> m_TPCube;

		//! Reference to our Renderer
		std::shared_ptr<Renderer> m_renderer;
		//! Reference to our Text Renderer
		std::shared_ptr<Renderer> m_textRenderer;
		std::shared_ptr<Shader> m_textShader;
		std::shared_ptr<VertexArray> m_textVAO;
		std::shared_ptr<Texture> m_textTexture;
		std::shared_ptr<Material> m_textMaterial;


		SceneData sceneData;

		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?

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