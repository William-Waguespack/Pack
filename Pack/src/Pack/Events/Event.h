#pragma once

#include "Pack/Core.h"

#include <string>
#include <functional>

namespace Pack
{


	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus,
		WindowLostFocus, WindowMoved, AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput =	   BIT(1),
		EventCategoryKeyboard =    BIT(2),
		EventCategoryMouse =       BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	class PACK_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		inline virtual std::string ToString() const { return GetName();}
		inline bool getHandled() const { return m_Handeled; }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handeled = false;
	};


	class PACK_API EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& event) : m_Event(event) {}


		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handeled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	inline std::string format_as(const Event& e)
	{
		return e.ToString();
	}
}