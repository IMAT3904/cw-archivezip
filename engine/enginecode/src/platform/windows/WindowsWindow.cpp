/** \file WindowsWindow.cpp
*/

#include "engine_pch.h"
#include "../platform/windows/WindowsWindow.h"


#ifdef NG_PLATFORM_WINDOWS	
#include "include/platform/OpenGL/OpenGLGLFWGraphicsContext.h"
#endif


namespace Engine {
	
	Window* Window::create(const WindowProperties& properties) 
	{
		return new WindowsWindow(properties);
	}
	
	WindowsWindow::WindowsWindow(const WindowProperties & properties)
	{
		init(properties);
	}

	void WindowsWindow::init(const WindowProperties & properties)
	{
		m_data.title = properties.m_title;
		m_data.height = properties.m_height;
		m_data.width = properties.m_width;
		m_data.fScreen = properties.m_isFullScreen;
		
		m_window = glfwCreateWindow((int)properties.m_width, (int)properties.m_height, m_data.title.c_str(), nullptr, nullptr);
		
#ifdef NG_PLATFORM_WINDOWS	
		m_context = std::shared_ptr<GraphicsContext>(new OpenGL_GLFWGraphicsContext(m_window));
#endif
		m_context->init();
		
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressed event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleased event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

	}

	WindowsWindow::~WindowsWindow()
	{
		close();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vSync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.vSync;
	}

	void WindowsWindow::close()
	{
		glfwDestroyWindow(m_window);
	}

}
