#pragma once
#include "events/event.h"

namespace Engine {
	
	class KeyPressedEvent : public Event
	{
	private:
		int keyCode = 0;
		int repeatCount = 0;
	public:
		KeyPressedEvent(int keycode, int repeatCount) : keyCode(keycode), repeatCount(repeatCount){}
		static EventType getStaticType() { return EventType::KeyPressed; }
		EventType getEventType() const override { return EventType::KeyPressed; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }

		inline int getKeyCode() const { return keyCode; }
		inline int getRepeatCount() const { return repeatCount; }

	};
	
	class KeyReleasedEvent : public Event
	{
	private:
		int keyCode = 0;
	public:
		KeyReleasedEvent(int keycode) : keyCode(keycode) {}
		static EventType getStaticType() { return EventType::KeyReleased; }
		EventType getEventType() const override { return EventType::KeyReleased; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }
		
		inline int getKeyCode() const { return keyCode; }
	};
	
	class KeyTypedEvent : public Event
	{
	private:
		int keyCode = 0;
	public:
		KeyTypedEvent(int keycode) : keyCode(keycode) {}
		static EventType getStaticType() { return EventType::KeyTyped; }
		EventType getEventType() const override { return EventType::KeyTyped; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }

		inline int getKeyCode() const { return keyCode; }
	};

}