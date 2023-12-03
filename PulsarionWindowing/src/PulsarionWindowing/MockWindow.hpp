#pragma once

#include "Window.hpp"

namespace Pulsarion::Windowing
{
	class MockWindow : public Window
	{
	public:
		MockWindow(const WindowInfo& info)
			: Window(info), m_Closed(false), m_Focused(false), m_Entered(false), m_MouseX(0), m_MouseY(0), m_Width(info.Width), m_Height(info.Height)
		{
		}

		~MockWindow() override
		{
		}

		void OnUpdate() override
		{
			// We don't need to do anything here
		}

		bool ShouldClose() const override
		{
			return m_Closed;
		}

		void SetVSync(bool enabled) override
		{
			m_Info.VSync = enabled;
		}

		void SetFullscreen(bool enabled) override
		{
			m_Info.Fullscreen = enabled;
		}

		// MockWindow functions for testing

		// Simulates pressing the close button
		void Close()
		{
			if (!m_Closed)
			{
				WindowCloseEvent event;
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}
			m_Closed = true;
		}

		// Simulates focusing the window
		void Focus()
		{
			if (!m_Focused)
			{
				WindowFocusEvent event;
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}
			m_Focused = true;
		}

		// Simulates unfocusing the window
		void Unfocus()
		{
			if (m_Focused)
			{
				WindowLostFocusEvent event;
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}
			m_Focused = false;
		}

		// Simulates entering the window
		void Enter()
		{
			if (!m_Entered)
			{
				MouseEnterEvent event;
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}
			m_Entered = true;
		}

		// Simulates leaving the window
		void Leave()
		{
			if (m_Entered)
			{
				MouseLeaveEvent event;
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}
			m_Entered = false;
		}

		// Simulates moving the mouse
		void MoveMouse(std::uint32_t x, std::uint32_t y)
		{
			Enter(); // If the mouse is moved, it must be in the window

			if (x != m_MouseX || y != m_MouseY)
			{
				MouseMovedEvent event(x, y);
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}
			m_MouseX = x;
			m_MouseY = y;
		}

		// Simulates resizing the window
		void Resize(std::uint32_t width, std::uint32_t height)
		{
			if (width != m_Width || height != m_Height)
			{
				WindowResizeEvent event(width, height);
				if (m_Info.EventCallback != nullptr)
					m_Info.EventCallback(event);
			}

			m_Width = width;
			m_Height = height;
		}

		// Simulates pressing a key
		void PressKey(KeyCode key)
		{
			KeyPressedEvent event(key, 0);
			if (m_Info.EventCallback != nullptr)
				m_Info.EventCallback(event);
		}

		// Simulates releasing a key
		void ReleaseKey(KeyCode key)
		{
			KeyReleasedEvent event(key);
			if (m_Info.EventCallback != nullptr)
				m_Info.EventCallback(event);
		}

		// Simulates typing a character
		void TypeChar(KeyCode key)
		{
			KeyTypedEvent event(key);
			if (m_Info.EventCallback != nullptr)
				m_Info.EventCallback(event);
		}

		// Simulates scrolling the mouse
		void Scroll(std::int32_t x, std::int32_t y)
		{
			if (x == 0 && y == 0)
				return; // No scrolling occurred (this is a no-op)

			MouseScrollEvent event(x, y);
			if (m_Info.EventCallback != nullptr)
				m_Info.EventCallback(event);
		}

		// Simulates pressing a mouse button
		void PressMouseButton(MouseCode button)
		{
			MouseButtonPressedEvent event(button);
			if (m_Info.EventCallback != nullptr)
				m_Info.EventCallback(event);
		}

		// Simulates releasing a mouse button
		void ReleaseMouseButton(MouseCode button)
		{
			MouseButtonReleasedEvent event(button);
			if (m_Info.EventCallback != nullptr)
				m_Info.EventCallback(event);
		}

	private:
		bool m_Closed;
		bool m_Focused;
		bool m_Entered;
		std::uint32_t m_MouseX;
		std::uint32_t m_MouseY;
		std::uint32_t m_Width;
		std::uint32_t m_Height;
	};
}
