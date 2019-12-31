/** \file application.cpp
*/

#include "engine_pch.h"

#pragma region TempIncludes
// temp includes
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#pragma endregion TempIncludes

#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
	#include "include/platform/windows/GLFWWindowSystem.h"
#endif //NG_PLATFORM_WINDOWS

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_log.reset(new Logger);		//Start our logger
		m_log->start();
		LOG_WARN("Log Initialized");

		m_timer.reset(new Timer);
		m_timer->start();	//Start our frame counter
		LOG_WARN("Frame Counter Started");

		// Start windows system
#ifdef NG_PLATFORM_WINDOWS	
		m_windowsSystem = std::shared_ptr<WindowSystem>(new GLFWWindowSystem());
		LOG_WARN("GLFW Window System Started");
#endif
		m_windowsSystem->start();
		LOG_WARN("Window System Started");

		m_window = std::shared_ptr<Window>(Window::create());
		LOG_WARN("Window Created");

		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
		LOG_WARN("Window Event Callback Set");

		// Enable standard depth detest (Z-buffer)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	
		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		unsigned int indices[3 * 12] = {
		2, 1, 0,
		0, 3, 2,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		14, 13, 12,
		12, 15, 14,
		18, 17, 16,
		16, 19, 18,
		20, 21, 22,
		22, 23, 20
		};

		BufferLayout FCLayout = {
			{ShaderDataType::Float3},
			{ShaderDataType::Float3}
		};

		m_vertexArrayFC.reset(VertexArray::create());
		m_vertexArrayFC->bind();
		std::shared_ptr<VertexBuffer> m_vertexBufferFC(VertexBuffer::create(FCvertices, sizeof(FCvertices)));
		m_vertexBufferFC->setLayout(FCLayout);
		m_vertexArrayFC->setVertexBuffer(m_vertexBufferFC);
		std::shared_ptr<IndexBuffer> m_indexBufferFC(IndexBuffer::create(indices, sizeof(indices)));
		m_vertexArrayFC->setIndexBuffer(m_indexBufferFC);
		m_FCShader.reset(Shader::create("assets/shaders/flatColour.glsl"));



#pragma region TempSetup
		
	
		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};

		BufferLayout TPLayout = {
			{ShaderDataType::Float3},
			{ShaderDataType::Float3},
			{ShaderDataType::Float2}
		};

		m_vertexArrayTP.reset(VertexArray::create());
		m_vertexArrayTP->bind();
		std::shared_ptr<VertexBuffer>m_vertexBufferTP(VertexBuffer::create(TPvertices, sizeof(TPvertices)));
		m_vertexBufferTP->setLayout(TPLayout);
		std::shared_ptr<IndexBuffer>m_indexBufferTP(IndexBuffer::create(indices, sizeof(indices)));
		m_vertexArrayTP->setVertexBuffer(m_vertexBufferTP);
		m_vertexArrayTP->setIndexBuffer(m_indexBufferTP);
		m_TPShader.reset(Shader::create("assets/shaders/texturedPhong.glsl"));

		m_FCTex->createFromFile("assets/textures/letterCube.png");
		m_TPTex->createFromFile("assets/textures/numberCube.png");

		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

		// End temporary code

#pragma endregion TempSetup

		m_timer->frameDuration(); //reset our timer
	}

	Application::~Application()
	{
		m_window.reset();
		m_windowsSystem->stop();
		m_timer->stop();
		m_log->stop();
		
	}

	void Application::run()
	{
		float fpsControl = 0.f;
		m_running = true;		//start run/frame/event loop
		while (m_running) {		//while the application is running
			
			frameDuration = m_timer->frameDuration();				//calculate frame duration
			fpsControl += frameDuration;

			LOG_INFO("FPS:{0}.", (int)(1.0f / frameDuration));	//convert into and show fps

			if (fpsControl > 1.f)
			{
				
				fpsControl = 0.f;
			}

#pragma region TempDrawCode
			// Temporary draw code to be abstracted

			glClearColor(0.8f, 0.8f, 0.8f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move, you can ignore this more or less.
			glm::mat4 FCtranslation, TPtranslation;

			if (m_goingUp)
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * frameDuration, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * frameDuration, 0.0f));
			}
			else
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * frameDuration, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * frameDuration, 0.0f));
			}

			m_timeSummed += frameDuration;
			if (m_timeSummed > 20.0f) {
				m_timeSummed = 0.f;
				m_goingUp = !m_goingUp;
			}

			
			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * frameDuration, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * frameDuration, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			

			// End of code to make the cube move.

			glm::mat4 fcMVP = projection * view * FCmodel;

			m_FCShader->bind();
			m_vertexArrayFC->bind();
			
			GLuint MVPLoc = glGetUniformLocation(m_FCShader->id(), "u_MVP");
			glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &fcMVP[0][0]);

			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

			glm::mat4 tpMVP = projection * view * TPmodel;
			unsigned int texSlot;
			if (m_goingUp) texSlot = m_textureSlots[0];
			else texSlot = m_textureSlots[1];

			m_TPShader->bind();
			m_vertexArrayTP->bind();

			MVPLoc = glGetUniformLocation(m_TPShader->id(), "u_MVP");
			glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &tpMVP[0][0]);

			GLuint modelLoc = glGetUniformLocation(m_TPShader->id(), "u_model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TPmodel[0][0]);

			GLuint colLoc = glGetUniformLocation(m_TPShader->id(), "u_objectColour");
			glUniform3f(colLoc, 0.2f, 0.8f, 0.5f);

			GLuint lightColLoc = glGetUniformLocation(m_TPShader->id(), "u_lightColour");
			glUniform3f(lightColLoc, 1.0f, 1.0f, 1.0f);

			GLuint lightPosLoc = glGetUniformLocation(m_TPShader->id(), "u_lightPos");
			glUniform3f(lightPosLoc, 1.0f, 4.0f, -6.0f);

			GLuint viewPosLoc = glGetUniformLocation(m_TPShader->id(), "u_viewPos");
			glUniform3f(viewPosLoc, 0.0f, 0.0f, -4.5f);

			GLuint texDataLoc = glGetUniformLocation(m_TPShader->id(), "u_texData");
			glUniform1i(texDataLoc, texSlot);

			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

			// End temporary code
#pragma endregion TempDrawCode

			m_window->onUpdate();									//frame
		}
	}

	void Application::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onClose));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(onResize));
		dispatcher.dispatch<WindowLostFocus>(BIND_EVENT_FN(onLostFocus));
		dispatcher.dispatch<WindowMovedEvent>(BIND_EVENT_FN(onWinMoved));
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
		LOG_WARN("Closing Application");
		m_running = false;
		return true;
	}

	bool Application::onResize(WindowResizeEvent & e)
	{
		LOG_INFO("Window Resized to {0}x{1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onLostFocus(WindowLostFocus & e)
	{
		LOG_INFO("Window lost focus at {0} , {1}", e.getXPos(), e.getYPos());
		return true;
	}

	bool Application::onWinMoved(WindowMovedEvent & e)
	{
		LOG_INFO("Window moved!");
		return true;
	}

	bool Application::onKeyPressed(KeyPressedEvent & e)
	{
		LOG_INFO("Key Pressed: {0}, R#:{1}", e.getKeyCode(), e.getRepeatCount());
		return true;
	}

	bool Application::onKeyReleased(KeyReleasedEvent & e)
	{
		LOG_INFO("Key Released: {0}", e.getKeyCode());
		return true;
	}

	bool Application::onKeyTyped(KeyTypedEvent & e)
	{
		LOG_INFO("Key Typed: {0}", e.getKeyCode());
		return true;
	}

	bool Application::onMbPressed(MouseButtonPressed & e)
	{
		LOG_INFO("Mouse button pressed: {0}", e.getButton());
		return true;
	}

	bool Application::onMbReleased(MouseButtonReleased & e)
	{
		LOG_INFO("Mouse button released: {0}", e.getButton());
		return true;
	}

	bool Application::onMouseMoved(MouseMovedEvent & e)
	{
		LOG_INFO("Mouse moved at: {0},{1}", e.getXPos(), e.getYPos());
		return true;
	}

	bool Application::onMouseScrolled(MouseScrolledEvent & e)
	{
		LOG_INFO("Mouse scrolled at: {0},{1}", e.getXPos(), e.getYPos());
		return true;
	}

}


