/** \file inputPollerGLFW.h
*	\brief This header contains the glfw implementation of an input poller
*/
#pragma once
#include "../independent/events/inputPoller.h"
#include "../platform/codes/codesGLFW.h"
#include "GLFW/glfw3.h"

namespace Engine {
	
	/**	\class inputPollerGLFW
	*	\brief Class which allows for input polling on a glfw window from anywhere in the code.
	*/
	class inputPollerGLFW : public InputPoller
	{
	private:
		float x, y;
	protected:
		bool isKeyPressedData(int keycode) override;
		bool isMouseButtonPressedData(int button) override;
		glm::vec2 getMousePositionData() override;
		float getMouseXData() override;
		float getMouseYData() override;
	};
}
