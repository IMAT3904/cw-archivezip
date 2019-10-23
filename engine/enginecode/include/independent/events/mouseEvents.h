#pragma once
#include "events/event.h"

namespace Engine {

	class MouseButtonPressed : public Event
	{
	private:
		int Button = 0;
	public:
		MouseButtonPressed(int button) : Button(button) {}
		static EventType getStaticType() { return EventType::MouseButtonPressed; }
		EventType getEventType() const override { return EventType::MouseButtonPressed; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getButton() const { return Button; }

	};

	class MouseButtonReleased : public Event
	{
	private:
		int Button = 0;
	public:
		MouseButtonReleased(int button) : Button(button) {}
		static EventType getStaticType() { return EventType::MouseButtonReleased; }
		EventType getEventType() const override { return EventType::MouseButtonReleased; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getButton() const { return Button; }

	};
	
	class MouseMovedEvent : public Event
	{
	private:
		float xPos;
		float yPos;
	public:
		MouseMovedEvent(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}
		static EventType getStaticType() { return EventType::MouseMoved; }
		EventType getEventType() const override { return EventType::MouseMoved; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline float getXPos() const { return xPos; }
		inline float getYPos() const { return yPos; }

	};
	
	class MouseScrolledEvent : public Event
	{
	private:
		float xPos;
		float yPos;
	public:
		MouseScrolledEvent(float xPos, float yPos) : xPos(xPos), yPos(yPos)  {}
		static EventType getStaticType() { return EventType::MouseScrolled; }
		EventType getEventType() const override { return EventType::MouseScrolled; }

		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline float getXPos() const { return xPos; }
		inline float getYPos() const { return yPos; }

	};

}