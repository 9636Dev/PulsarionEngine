#pragma once

#pragma once

#include <PulsarionCore/Core.hpp>

#include "KeyCodes.hpp"
#include "Event.hpp"

#include <sstream>

namespace Pulsarion::Windowing {

    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }
        virtual std::uint32_t GetCategoryFlags() const override { return static_cast<std::int32_t>(EventCategory::Input) | static_cast<std::uint32_t>(EventCategory::Keyboard); }
        
    protected:
        KeyEvent(const KeyCode keycode)
            : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode p_Keycode, bool p_IsRepeat = false)
            : KeyEvent(p_Keycode), m_IsRepeat(p_IsRepeat) {}

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << static_cast<std::uint16_t>(m_KeyCode) << " (repeat = " << m_IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode p_Keycode)
            : KeyEvent(p_Keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent (Key: " << static_cast<std::uint16_t>(m_KeyCode) << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const KeyCode p_Keycode)
            : KeyEvent(p_Keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent (Key: " << static_cast<std::uint16_t>(m_KeyCode) << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}
