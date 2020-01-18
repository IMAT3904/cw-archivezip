/** \file .h
*	\brief
*/

#pragma once
#include "camera.h"

namespace Engine {

	class OrthographicCamera2D : public Camera
	{
	private:
		glm::vec3 m_position;
		float m_rotation = 0.f;
		void updateView() override;
	public:
		
		OrthographicCamera2D(float left, float right, float bottom, float top);
		
		inline glm::vec3 getPosition() const { return m_position; }
		inline float getRotation() const { return m_rotation; }
		
		void setPosition(const glm::vec3& position) { m_position = position; updateView(); }
		void setRotation(float rotation) { m_rotation = rotation; updateView(); }
		void setPositionRotation(const glm::vec3& position, float rotation) 
		{ m_position = position; updateView(); m_rotation = rotation; updateView();	}
	};
}