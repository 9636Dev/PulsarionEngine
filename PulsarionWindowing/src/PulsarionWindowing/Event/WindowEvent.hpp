#pragma once

#include <PulsarionCore/Core.hpp>

#include "Event.hpp"

#include <sstream>

namespace Pulsarion::Windowing {

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int p_Width, unsigned int p_Height)
            : m_Width(p_Width), m_Height(p_Height) {}

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent (" << m_Width << ", " << m_Height << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Window); }
    private:
        unsigned int m_Width, m_Height;
    };

    class WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent() = default;

        inline std::string ToString() const override { return "WindowFocusEvent"; }

        EVENT_CLASS_TYPE(WindowFocus)
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Window); }
    };

    class WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() = default;

		inline std::string ToString() const override { return "WindowLostFocusEvent"; }

		EVENT_CLASS_TYPE(WindowLostFocus)
		virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Window); }
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        inline std::string ToString() const override { return "WindowCloseEvent"; }

        EVENT_CLASS_TYPE(WindowClose)
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Window); }
    };
}