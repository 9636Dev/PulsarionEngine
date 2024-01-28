#pragma once

#include <PulsarionCore/Core.hpp>

#include "Event/Events.hpp"
#include "Core.hpp"

#include <string>
#include <functional>
#include <memory>

namespace Pulsarion::Windowing
{
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowCreateInfo
	{
		std::string Title;
		std::uint32_t Width;
		std::uint32_t Height;
		/// <summary>
		/// If enabled, the window will be created in fullscreen mode.
		/// </summary>
		bool Fullscreen;
		bool VSync;

		WindowCreateInfo(const std::string& title = "Pulsarion Engine", std::uint32_t width = 1280, std::uint32_t height = 720, bool fullscreen = false, bool vsync = true)
			: Title(title), Width(width), Height(height), Fullscreen(fullscreen), VSync(vsync)
		{
		}
	};

	struct WindowInfo // This is stored inside the window to synchronize the window with the window info.
	{
		std::string Title;
		std::uint32_t Width;
		std::uint32_t Height;
		bool Fullscreen;
		bool VSync;
		EventCallbackFn EventCallback;

		WindowInfo(const std::string& title = "Pulsarion Engine", std::uint32_t width = 1280, std::uint32_t height = 720, bool fullscreen = false, bool vsync = true)
			: Title(title), Width(width), Height(height), Fullscreen(fullscreen), VSync(vsync)
		{
		}

		// From CreateInfo
		WindowInfo(const WindowCreateInfo& info)
			: Title(info.Title), Width(info.Width), Height(info.Height), Fullscreen(info.Fullscreen), VSync(info.VSync)
		{
		}
	};

    enum class StandardCursorShape
    {
        Arrow,
        IBeam,
        Crosshair,
        Hand,
        HResize,
        VResize,
        NWSEResize,
        NESWResize,
        AllResize,
        NotAllowed,
    };
	
	class Window
	{
	public:
		friend PULSARION_WINDOWING_API std::shared_ptr<Window> CreateWindow(const WindowCreateInfo& info);

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual bool ShouldClose() const = 0;

		inline virtual std::uint32_t GetWidth() const { return m_Info.Width; };
		inline virtual std::uint32_t GetHeight() const { return m_Info.Height; };

		inline virtual void SetEventCallback(const EventCallbackFn& callback) { m_Info.EventCallback = callback; };
		 virtual void SetVSync(bool enabled) = 0;
		inline virtual bool IsVSync() const { return m_Info.VSync; };

		virtual void SetTitle(const std::string& title) = 0;
        virtual std::string GetTitle() const = 0;
		virtual void SetFullscreen(bool fullscreen) = 0;
		inline virtual bool IsFullscreen() const { return m_Info.Fullscreen; };
        virtual void SetCursorShape(StandardCursorShape shape) = 0;

		virtual void* GetNativeWindow() const = 0;

	protected:
		Window(const WindowInfo& info)
			: m_Info(info)
		{
		}

		WindowInfo m_Info;
	};

	extern PULSARION_WINDOWING_API std::shared_ptr<Window> CreateWindow(const WindowCreateInfo& info = WindowCreateInfo());
}
