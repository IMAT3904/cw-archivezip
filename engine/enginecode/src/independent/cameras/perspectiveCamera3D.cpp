/** \file .cpp
*	\brief
*/

#include "engine_pch.h"
#include "cameras/perspectiveCamera3D.h"

namespace Engine {
	
	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		reset(fov, aspectRatio, nearClip, farClip);
	}

	void PerspectiveCamera3D::reset(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}

	void PerspectiveCamera3D::updateView()
	{

	}

}