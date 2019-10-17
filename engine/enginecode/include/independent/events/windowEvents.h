#pragma once
#include "events/event.h"

namespace Engine {
	
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		static EventType getStaticType() { return EventType::WindowClose; }
		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class WindowResizeEvent : public Event
	{
	private:
		int m_width;
		int m_height;
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}
		static EventType getStaticType() { return EventType::WindowResize; }
		EventType getEventType() const override { return EventType::WindowResize; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

	};

	class WindowLostFocus : public Event
	{
	private:
		float xPos;
		float yPos;
	public:
		WindowLostFocus(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}
		static EventType getStaticType() { return EventType::WindowLostFocus; }
		EventType getEventType() const override { return EventType::WindowLostFocus; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline float getXPos() const { return xPos; }
		inline float getYPos() const { return yPos; }

	};

	class WindowMoved : public Event
	{
	private:
	public:
		WindowMoved() {}
		static EventType getStaticType() { return EventType::WindowMoved; }
		EventType getEventType() const override { return EventType::WindowMoved; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};


}

