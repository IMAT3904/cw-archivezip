#pragma once

#include <glm/glm.hpp>

namespace Engine {

	class InputPoller
	{
	private:
		static InputPoller * s_instance; //!< Single instance pointer 
	protected:
		virtual bool isKeyPressedData(int keycode) = 0;
		virtual bool isMouseButtonPressedData(int button) = 0;
		virtual glm::vec2 getMousePositionData() = 0;
		virtual float getMouseXData() = 0;
		virtual float getMouseYData() = 0;
	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedData(keycode); }
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedData(button); }
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionData(); }
		inline static float getMouseX() { return s_instance->getMouseXData(); }
		inline static float getMouseY() { return s_instance->getMouseYData(); }
	};
}
