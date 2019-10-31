/** \file event.h
*	\brief This header includes our Event class, and our event dispatcher. It also enumerates EventType and EventCategory, all which are needed for handling inputs
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

	/**	\class Event
	*	\brief The event class is an abstract class which defines our events.
	*/
	class Event {
	protected:
		bool m_handled = false; //!< bool to show if the event has been handled
	public:
		//! Returns the eventType of the event
		/*!
		\return the eventType of the event 
		*/
		virtual EventType getEventType() const = 0;
		
		//! Returns the category enum of the event
		/*!
		\return the enum value of the event category
		*/
		virtual int getCategoryFlags() const = 0;
		
		//! Checks if the event has been handled
		/*!
		\return bool if the event has been handled or not
		*/
		inline bool handled() const { return m_handled; }
		
		//! Sets the handled state of the event
		/*!
		\param isHandled input bool to set the state of the event
		*/
		inline void handle(bool isHandled) { m_handled = isHandled; }

		//! Checks if the event is in the category of the input category
		/*!
		\param category which category of event you want to check the event is
		\return returns true or false if the inputted category is the events category
		*/
		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}
	};

	/**
	\class Event Dispatcher
	* \brief The event dispatcher class is used to pass our events from wherever we may need to use them
	*/

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
		//!< Make EventFunc a func which returns a bool and a reference to our template
	public:
		EventDispatcher(Event& event) : m_event(event) //!< constructor which sets our reference
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
		//!< event reference - it is abstract
	};

}
