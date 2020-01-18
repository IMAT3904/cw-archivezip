/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "cameras/perspectiveCamera3D.h"

namespace Engine {
	
	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_orientation = glm::quat(0.f,0.f,0.f,0.f);

		updateView();
	}

	void PerspectiveCamera3D::updateView()
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

}