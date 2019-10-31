/** \file window.h
*	\brief This header contains the definition of a virtual and agnostic implementation of a window. 
*/
#pragma once
#include <functional>
#include "events/event.h"
#include "windows/graphicsContext.h"

namespace Engine {
	
	/** \struct WindowProperties
	*	\brief Struct which will define the elements of our window that it needs for creation
	*/
	struct WindowProperties
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_isFullScreen;
		bool m_isVSync;

		WindowProperties(const std::string& title = "My Window", 
			unsigned int width = 800, unsigned int height = 600, 
			bool fullscreen = false) : m_title(title), 
			m_width(width), m_height(height), m_isFullScreen(fullscreen) {}
	};

	/** \class Window
	*	\brief The window class is a virtual implementation of a window which will be overriden by a
	*	window using an API.
	*/
	class Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {};
		virtual void onUpdate() = 0;		
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual bool isVSync() const = 0;
		virtual void setVSync(bool VSync) = 0;
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0;
		virtual void* getNativeWindow() const = 0;
		virtual bool isFullScreenMode() const = 0;

		static Window* create(const WindowProperties& properties = WindowProperties());
	
	protected:
		std::shared_ptr<GraphicsContext> m_context;
	};

}