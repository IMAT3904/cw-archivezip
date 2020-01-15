/** \file .h
*	\brief
*/

#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "orthographicCamera2D.h"
#include "cameraController.h"


namespace Engine {

	class FreeOrthoCameraController2D : public CameraController
	{
	private:
		std::shared_ptr<OrthographicCamera2D> m_camera;
		glm::vec2 m_position = glm::vec3(0.f);
		float m_rotation = 0.f;
		float m_translationSpeed = 0.f;
		float m_rotationSpeed = 10.f;
	public:
		FreeOrthoCameraController2D();
		void init(float left, float top, float width, float height) override;
		std::shared_ptr<Camera> getCamera() override { return m_camera; }
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override {};
		void onResize() override {};
	};



}