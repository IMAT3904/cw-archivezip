#pragma once
#include "../independent/events/inputPoller.h"
#include "../platform/codes/codesGLFW.h"
#include "GLFW/glfw3.h"

namespace Engine {
	
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
