#pragma once

#include "PulsarionWindowing/Window.hpp"

#include <GLFW/glfw3.h>

namespace Pulsarion::Windowing
{
#ifdef PULSARION_RENDERER_OPENGL
	class GLInfo // Used to sync renderer with window GL version.
	{
	public:
		static std::int32_t GLVersionMajor;
		static std::int32_t GLVersionMinor;
	};
#endif // PULSARION_RENDERER_OPENGL

	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(const WindowCreateInfo& properties);
		virtual ~GlfwWindow();

		void OnUpdate() override;
		bool ShouldClose() const override;

		void SetVSync(bool enabled) override;
        void SetTitle(const std::string& title) override;
        std::string GetTitle() const override;
		void SetFullscreen(bool enabled) override;
        void SetCursorShape(StandardCursorShape shape) override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		void SetCallbacks();
        void SetCursor(GLFWcursor* cursor);

        std::string m_Title; // We have to store the title because GLFW doesn't have a way to get the title.

		GLFWwindow* m_Window;
        GLFWcursor* m_Cursor;
	};
}
