#pragma once

#include <PulsarionCore/Core.hpp>
#include <string>

// Utility Function
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
    virtual EventType GetEventType() const override	{ return GetStaticType(); }\
    virtual std::string GetName() const override { return #type; }

namespace Pulsarion::Windowing
{
	enum class EventType
	{
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseEnter,
		MouseLeave,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum class EventCategory : std::uint32_t
	{
		None = 0,
		Window = 1 << 0,
		Input = 1 << 1,
		Keyboard = 1 << 2,
		Mouse = 1 << 3,
		MouseButton = 1 << 4
	};

	class Event
	{
			friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual std::uint32_t GetCategoryFlags() const = 0;
		virtual std::string GetName() const = 0;
		virtual std::string ToString() const = 0;

		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & static_cast<std::uint32_t>(category);
		}

	private:
		bool m_Handled = false;	
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& func) // F is derived by the compiler.
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};
}
