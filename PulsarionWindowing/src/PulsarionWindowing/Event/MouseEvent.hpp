#pragma once

#include <PulsarionCore/Core.hpp>

#include "Event.hpp"
#include "MouseCodes.hpp"

#include <sstream>

namespace Pulsarion::Windowing {
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float p_MouseX, const float p_MouseY) :
            m_MouseX(p_MouseX), m_mouseY(p_MouseY) {}

        float GetMouseX() const { return m_MouseX; }
        float GetMouseY() const { return m_mouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent (Pos: " << m_MouseX << ", " << m_mouseY << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Mouse) | static_cast<std::uint32_t>(EventCategory::Input); }

    private:
        const float m_MouseX;
        const float m_mouseY;
    };

    class MouseEnterEvent : public Event {
    public:
        MouseEnterEvent() = default;

        std::string ToString() const override {
            return "MouseEnterEvent";
        }

        EVENT_CLASS_TYPE(MouseEnter);
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Mouse) | static_cast<std::uint32_t>(EventCategory::Input); }
    };
    
    class MouseLeaveEvent : public Event {
    public:
        MouseLeaveEvent() = default;

        std::string ToString() const override {
            return "MouseLeaveEvent";
        }

        EVENT_CLASS_TYPE(MouseLeave);
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Mouse) | static_cast<std::uint32_t>(EventCategory::Input); }
    };

    class MouseScrollEvent : public Event {
    public:
        MouseScrollEvent(const float p_OffsetX, const float p_OffsetY) :
            m_OffsetX(p_OffsetX), m_OffsetY(p_OffsetY) {}

        float GetOffsetX() const { return m_OffsetX; }
        float GetOffsetY() const { return m_OffsetY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrollEvent (Offset: " << m_OffsetX << ", " << m_OffsetY << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Mouse) | static_cast<std::uint32_t>(EventCategory::Input); }

    private:
        const float m_OffsetX;
        const float m_OffsetY;
    };

    class MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::uint32_t>(EventCategory::Mouse) | static_cast<std::uint32_t>(EventCategory::Input); }
    protected:
        MouseButtonEvent(const MouseCode button)
            : m_Button(button) {}

        MouseCode m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) {};

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent (Button: " << static_cast<std::uint16_t>(m_Button) << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent (Button:" << static_cast<std::uint16_t>(m_Button) << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}