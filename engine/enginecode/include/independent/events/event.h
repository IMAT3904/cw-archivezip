/** \file event.h
* This header includes our Event class, and our event dispatcher. It also enumerates EventType and EventCategory, all which are needed for handling inputs
*/
#pragma once

#include "engine_pch.h"

namespace Engine {
	
	//! Enum class for each type of event in the engine.
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	
	//! Enum class for categorising our events.
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4
	};

	/**
	\class Event
	* Our event class which defines what an event is
	*
	*
	*/
	class Event {
	protected:
		bool m_handled = false;
	public:
		virtual EventType getEventType() const = 0;
		virtual int getCategoryFlags() const = 0;
		inline bool handled() const { return m_handled; }
		inline void handle(bool isHandled) { m_handled = isHandled; }
		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}
	};

	/**
	\class Event Dispatcher
	*/

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
		//Make EventFunc a func which returns a bool and a reference to our template
	public:
		EventDispatcher(Event& event) : m_event(event) //constructor which sets our reference
		{
		}

		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
		//event reference - it is abstract
	};

}
