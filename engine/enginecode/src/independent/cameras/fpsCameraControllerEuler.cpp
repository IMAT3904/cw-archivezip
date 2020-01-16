/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/platform/GLFW/GLFWCodes.h"
#include "include/independent/events/inputPoller.h"
#include "cameras/fpsCameraControllerEuler.h"

namespace Engine {
	
	FPSCameraControllerEuler::FPSCameraControllerEuler()
	{
		init();
	}
	
	void FPSCameraControllerEuler::init(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_camera.reset(new PerspectiveCamera3D(fov, aspectRatio, nearClip, farClip));
		m_position = m_camera->getPosition();
		updateView();
	}

	void FPSCameraControllerEuler::updateView()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward = glm::normalize(forward);

		//recalc right and up vec
		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));

		//recalculate view matrix
		m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
		
		m_camera->setView(m_view);

	}

	void FPSCameraControllerEuler::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KB_KEY_W)) { m_position += m_forward * m_translationSpeed * timestep; }
		if(InputPoller::isKeyPressed(KB_KEY_S)) { m_position -= m_forward * m_translationSpeed * timestep; }
		if(InputPoller::isKeyPressed(KB_KEY_A)) { m_position -= m_right * m_translationSpeed * timestep; }
		if(InputPoller::isKeyPressed(KB_KEY_D)) { m_position += m_right * m_translationSpeed * timestep; }

		if (InputPoller::isMouseButtonPressed(MB_MOUSE_BUTTON_LEFT))
		{
			glm::vec2 currentMousePosition = InputPoller::getMousePosition();
			glm::vec2 mouseDelta = currentMousePosition - m_lastMousePosition;

			m_yaw += mouseDelta.x * m_rotationSpeed * timestep;
			m_pitch -= mouseDelta.y * m_rotationSpeed * timestep;

			if (m_pitch > 89.0f) m_pitch = 89.0f;
			if (m_pitch < -89.0f) m_pitch = -89.0f;

			m_lastMousePosition = currentMousePosition;
		}
	}

	void FPSCameraControllerEuler::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&FPSCameraControllerEuler::onMouseButton, this, std::placeholders::_1));
	}

	bool FPSCameraControllerEuler::onMouseButton(MouseButtonPressed & e)
	{
		if (e.getButton() == MB_MOUSE_BUTTON_LEFT)
			m_lastMousePosition = InputPoller::getMousePosition();
		return true;
	}
	
}