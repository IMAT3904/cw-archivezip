/** \file WindowsWindow.h
*/

#pragma once

#include "windows/window.h"
#include <GLFW/glfw3.h>
#include "events/event.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
#include "events/windowEvents.h"


namespace Engine {

	class WindowsWindow : public Window
	{
	private:

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFn EventCallback;
		};

		GLFWwindow* m_window;
		virtual void init(const WindowProperties& properties);
		virtual void shutdown();
		WindowData m_data;

	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();
		void onUpdate();

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		bool isVSync() const override;
		void setVSync(bool enabled) override;
		inline void setEventCallback(const EventCallbackFn& callback) override 
		{ m_data.EventCallback = callback; }

	
	};

}