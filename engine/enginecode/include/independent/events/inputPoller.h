/** \file inputPoller.h
*	\brief This header contains the class which can check for inputs from anywhere in the program.
*/
#pragma once

#include <glm/glm.hpp>

namespace Engine {

	/**
	\class InputPoller
	* \brief The input poller checks for an input and returns a true or false value based on the query.
	*/
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
