/** \file WindowsWindow.h
	\brief This is the Windows implementation of the window, using OpenGL, GLAD and GLFW
*/


#pragma once

#include "windows/window.h"
#include "events/event.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
#include "events/windowEvents.h"
#include "OpenGL_GLFWGraphicsContext.h"
#include "GLFW/glfw3.h"



namespace Engine {


	/**	\class WindowsWindow
	*	\brief This is the Windows implementation of the window, using OpenGL, GLAD and GLFW
	*/
	class WindowsWindow : public Window
	{
	private:

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync, fScreen;
			EventCallbackFn EventCallback;
		};

		WindowData m_data;
		GLFWwindow* m_window;
		virtual void init(const WindowProperties& properties);
		virtual void close();
	
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();
		void onUpdate();

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }
		virtual void* getNativeWindow() const override { return m_window; }
		bool isFullScreenMode() const override { return m_data.fScreen;  }

		bool isVSync() const override;
		void setVSync(bool enabled) override;
		inline void setEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
	};

}
