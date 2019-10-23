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
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		inline void setEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		
		void setVSync(bool enabled) override;
		bool isVSync() const override;
		void onUpdate();
	private:
		virtual void init(const WindowProperties& properties);
		virtual void shutdown();
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_data;
	};

}