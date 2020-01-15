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
	#include "include/platform/GLFW/GLFWWindowSystem.h"
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
		LOG_WARN("Logger Initialized");

		m_resources.reset(new ResourceManager);
		m_resources->start();
		LOG_WARN("Resource Manager Started");

		m_timer.reset(new Timer);
		m_timer->start();	//Start our frame counter
		LOG_WARN("Timing system Started");
		// Start windows system
#ifdef NG_PLATFORM_WINDOWS	
		m_windowsSystem = std::shared_ptr<WindowSystem>(new GLFWWindowSystem());
		LOG_WARN("GLFW Window System Started");
#endif
		m_windowsSystem->start();
		m_window = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
		LOG_WARN("Window Created");

		m_renderer.reset(Renderer::createBasic3D());
		LOG_WARN("Created Basic3D Renderer");

		m_textRenderer.reset(Renderer::createBasicTextRenderer2D());
		LOG_WARN("Created Basic3D Renderer");

		m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(RenderCommand::setBackfaceCullingCommand(true));		


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

		float textVertices[4 * 4] = {
			0.f, 0.f, 0.f, 0.0f,
			0.f, 271.f, 0.f, 1.f,
			644.f, 271.f, 1.0f, 1.f,
			644.f, 0.f, 1.0f, 0.0f,
		};

		unsigned int textIndices[4] = { 0,1,2,3 };

		VertexBufferLayout FCLayout = { {ShaderDataType::Float3},{ShaderDataType::Float3} };
		m_FCShader = m_resources->addShader("assets/shaders/flatColour.glsl");
		m_FCVAO = m_resources->addVAO("flatColorCube");
		m_FCVAO->setVertexBuffer(m_resources->addVBO("FlatColorVBO", FCvertices, sizeof(FCvertices), FCLayout));
		m_FCVAO->setIndexBuffer(m_resources->addIndexBuffer("CubeIndices", indices, 3 * 12));
		m_FCCube = m_resources->addMaterial("FCCUBE", m_FCShader, m_FCVAO);

		VertexBufferLayout TPLayout = { {ShaderDataType::Float3},{ShaderDataType::Float3},{ShaderDataType::Float2} };
		m_TPShader = m_resources->addShader("assets/shaders/texturedPhong.glsl");
		m_TPVAO = m_resources->addVAO("texturedPhongCube");
		m_TPVAO->setVertexBuffer(m_resources->addVBO("texturedPhongVBO", TPvertices, sizeof(TPvertices), TPLayout));
		m_TPVAO->setIndexBuffer(m_resources->addIndexBuffer("CubeIndices", indices, 3 * 12));
		m_TPCube = m_resources->addMaterial("TPCUBE", m_TPShader, m_TPVAO);
		

		VertexBufferLayout textLayout = { {ShaderDataType::Float2},{ShaderDataType::Float2} };
		m_textShader = m_resources->addShader("assets/shaders/text.glsl");
		m_textVAO = m_resources->addVAO("textVAO");
		m_textVAO->setVertexBuffer(m_resources->addVBO("textVBO", textVertices, sizeof(textVertices), textLayout));
		m_textVAO->setIndexBuffer(m_resources->addIndexBuffer("textIBO", textIndices, 4));
		m_textMaterial = m_resources->addMaterial("TEXT", m_textShader, m_textVAO);
		
		m_textTexture = m_resources->addTexture("assets/textures/hello.png");

		m_texLetter = m_resources->addTexture("assets/textures/letterCube.png");
		m_texNumber = m_resources->addTexture("assets/textures/numberCube.png");

		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));
		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));

		glm::mat4 textProjection = glm::ortho(0.f, 800.f, 600.f, 0.f);
		glm::mat4 textView = glm::mat4(1.0f);
		glm::mat4 textMode = glm::translate(glm::mat4(1.0f), glm::vec3(100.f, 100.f, 0.f));


		/*
		UniformBufferLayout uboMatricesLayout = { {ShaderDataType::Mat4},{ShaderDataType::Mat4} };
		m_UBOMatrices = m_resources->addUBO("Matrices", 2 * sizeof(glm::mat4), uboMatricesLayout);
		m_UBOMatrices->attachShaderBlock(m_FCShader, "Matrices");
		m_UBOMatrices->attachShaderBlock(m_TPShader, "Matrices");
		UniformBufferLayout uboLightsLayout = { {ShaderDataType::Float3},{ShaderDataType::Float3},{ShaderDataType::Float3} };
		m_UBOLights = m_resources->addUBO("Lights", 3 * sizeof(glm::mat4), uboLightsLayout);
		m_UBOLights->attachShaderBlock(m_TPShader, "Lights");
		*/

		m_timer->frameDuration(); //reset our timer
	}

	Application::~Application()
	{
		m_window.reset();
		LOG_INFO("Cleared Window");
		m_windowsSystem->stop();
		LOG_INFO("Windows System Stopped");
		m_resources.reset();
		LOG_INFO("Cleared Resource System");
		m_timer->stop();
		LOG_INFO("Timer Stopped");
		LOG_INFO("Ending Log...");
		m_log->stop();
		
	}

	void Application::run()
	{
		m_running = true;		//start run/frame/event loop
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
			glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
			glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
		);

		glm::vec3 m_lightPosition = glm::vec3(1.0f, 4.0f, -6.0f);
		glm::vec3 m_viewPosition = glm::vec3(0.0f, 0.0f, -4.5f);
		glm::vec3 m_lightColour = glm::vec3(1.0f, 1.0f, 1.0f);

		/*
		std::vector<void*> sceneData1(2);
		sceneData1[0] = (void*)&projection[0][0];
		sceneData1[1] = (void*)&view[0][0];
		std::vector<void*> sceneData2(3);
		sceneData2[0] = (void*)&m_lightPosition[0];
		sceneData2[1] = (void*)&m_viewPosition[0];
		sceneData2[2] = (void*)&m_lightColour[0];
		SceneData sceneData;
		sceneData[m_UBOMatrices] = sceneData1;
		sceneData[m_UBOLights] = sceneData1;
		*/

		m_renderer->actionCommand(RenderCommand::setClearColourCommand(0.8f, 0.8f, 0.8f, 1.f));

		glm::mat4 textProjection = glm::ortho(0.f, 800.f, 600.f, 0.f);
		glm::mat4 textView = glm::mat4(1.0f);
		glm::mat4 textModel = glm::translate(glm::mat4(1.0f), glm::vec3(100.f, 100.f, 0.f));


		while (m_running) {		//while the application is running
			
			frameDuration = m_timer->frameDuration();				//calculate frame duration
			fpsControl += frameDuration;

			//print fps to console every second
			if (fpsControl > 5.f)
			{
				LOG_INFO("FPS:{0}.", (int)(1.0f / frameDuration));	//convert into and show fps
				fpsControl = 0.f;
			}

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
			

			// Flat Cube
			glm::mat4 fcMVP = projection * view * FCmodel;

			// Textured Phong
			glm::mat4 tpMVP = projection * view * TPmodel;
			if (m_goingUp) m_texSlot = m_texLetter->getSlot();
			else m_texSlot = m_texNumber->getSlot();

			m_renderer->actionCommand(RenderCommand::ClearDepthColorBufferCommand());

			//m_renderer->beginScene(sceneData);
			
			//ubo stuff
			m_FCCube->setDataElement("u_MVP", &fcMVP[0][0]);
			m_renderer->submit(m_FCCube);

			m_TPCube->setDataElement("u_model", &TPmodel[0][0]);
			m_TPCube->setDataElement("u_texData", &m_texSlot);
			//ubo stuff
			m_TPCube->setDataElement("u_MVP", &tpMVP[0][0]);
			m_TPCube->setDataElement("u_lightColour", &m_lightColour[0]);
			m_TPCube->setDataElement("u_lightPos", &m_lightPosition[0]);
			m_TPCube->setDataElement("u_viewPos", &m_viewPosition[0]);
			m_renderer->submit(m_TPCube);

			m_texSlot = m_textTexture->getSlot();

			m_textMaterial->setDataElement("u_projection", (void*)&textProjection[0][0]);
			m_textMaterial->setDataElement("u_view", (void*)&textView[0][0]);
			m_textMaterial->setDataElement("u_model", (void*)&textModel[0][0]);
			m_textMaterial->setDataElement("u_texData", (void*)&m_texSlot);

			m_textRenderer->actionCommand(RenderCommand::setOneMinusAlphaBlending(true));
			m_textRenderer->submit(m_textMaterial);
			m_textRenderer->actionCommand(RenderCommand::setOneMinusAlphaBlending(false));

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


