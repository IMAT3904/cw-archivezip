/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "include/independent/events/inputPoller.h"
#include "include/platform/GLFW/GLFWCodes.h"
#include "cameras/freeOrthoCameraController2D.h"

namespace Engine {

	FreeOrthoCameraController2D::FreeOrthoCameraController2D(float translateSpeed)
	{
		m_translationSpeed = translateSpeed;
	}

	void FreeOrthoCameraController2D::init(float left, float top, float width, float height)
	{
		m_camera = std::make_shared<OrthographicCamera2D>(left, top, width, height);

		m_position = m_camera->getPosition();
		m_rotation = m_camera->getRotation();
	}

	void FreeOrthoCameraController2D::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KB_KEY_UP))
		{
			m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KB_KEY_LEFT))
		{
			m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KB_KEY_DOWN))
		{
			m_position.x += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KB_KEY_RIGHT))
		{
			m_position.x += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;

		}

		m_camera->setPosition(m_position);
	}
}