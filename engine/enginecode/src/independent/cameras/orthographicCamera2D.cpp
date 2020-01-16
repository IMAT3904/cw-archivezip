/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "cameras/orthographicCamera2D.h"
#include <glm/gtc/matrix_transform.hpp>	

namespace Engine {
	
	OrthographicCamera2D::OrthographicCamera2D(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top);
		m_view = glm::mat4(1.0f);
		m_viewProjection = m_view * m_projection;

		m_position = glm::vec3(0.0f);
		m_rotation = 0.0f;
	}
	
	void OrthographicCamera2D::updateView()
	{
	}
	
	void OrthographicCamera2D::reset(float left, float right, float bottom, float top)
	{
	}
}