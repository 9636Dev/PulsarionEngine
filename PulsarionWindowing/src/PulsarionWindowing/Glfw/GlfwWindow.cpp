#include "GlfwWindow.hpp"

#include <PulsarionCore/Log.hpp>
#include <PulsarionCore/Assert.hpp>

namespace Pulsarion::Windowing
{
    std::int32_t GLInfo::GLVersionMajor = 0;
    std::int32_t GLInfo::GLVersionMinor = 0;

	class GLFW
    {
    public:
        static void Init()
        {
            if (s_Initialized)
                return;

            // Setup error callback to log errors if initialization fails
            glfwSetErrorCallback(GLFWErrorCallback);

            if (!glfwInit())
            {
                PULSARION_CORE_LOG_FATAL("Failed to initialize GLFW!");
                std::abort();
                return;
            }
        }

        static GLFWwindow* NewNonApiWindow(const WindowInfo& info)
		{
			Init();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			GLFWwindow* window = glfwCreateWindow(info.Width, info.Height, info.Title.c_str(), nullptr, nullptr);

            if (window == nullptr)
			{
				PULSARION_CORE_LOG_ERROR("Failed to create window!");
				return nullptr;
			}

			return window;
		}

        static GLFWwindow* NewWindow(const WindowInfo& info)
        {
            Init();
            
            if (s_GLVersionMajor > 0)
            {
				GLFWwindow* window = RequestVersionForWindow(info, s_GLVersionMajor, s_GLVersionMinor);

				if (window != nullptr)
					return window;

                PULSARION_CORE_LOG_ERROR("Failed to create window with version {}.{}!", s_GLVersionMajor, s_GLVersionMinor);
                return nullptr;
            }

            // Try each version from newest to oldest
            std::int32_t versions[] = {
            	4, 6,
				4, 5,
				4, 4,
				4, 3,
				4, 2,
				4, 1,
            };
            // Lowest we support is 4.1, as we use uniform buffer objects and support for MacOS is dropped after 4.1

            for (std::size_t i = 0; i < std::size(versions); i += 2)
			{
				GLFWwindow* window = RequestVersionForWindow(info, versions[i], versions[i + 1]);

                if (window == nullptr)
                {
                    continue; // Try next version
                }

                s_GLVersionMajor = versions[i];
                s_GLVersionMinor = versions[i + 1];
                GLInfo::GLVersionMajor = versions[i]; // Sync GLInfo with window
                GLInfo::GLVersionMinor = versions[i + 1];

                return window;
			}

            PULSARION_CORE_LOG_ERROR("Failed to create window with any version!");
			return nullptr;
        }

        static void Shutdown(GLFWwindow* window)
        {
            if (!s_Initialized)
                return;

            if (window == nullptr)
            {
                PULSARION_CORE_LOG_WARN("Tried to shutdown GLFW without a window!");
                return;
            }

            glfwDestroyWindow(window);

            if (--s_WindowCount != 0)
                return;

            glfwTerminate();
        }

    private:
        static void GLFWErrorCallback(int error, const char* description)
        {
            PULSARION_CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
        }

        static GLFWwindow* RequestVersionForWindow(const WindowInfo& info, std::int32_t versionMajor, std::int32_t versionMinor)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
            PULSARION_RUN_IF_DEBUG(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE));
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

            GLFWwindow* window = glfwCreateWindow(info.Width, info.Height, info.Title.c_str(), nullptr, nullptr);

            if (window != nullptr)
            {
                s_GLVersionMajor = versionMajor;
                s_GLVersionMinor = versionMinor;
                glfwShowWindow(window);
                return window;
            }

            return nullptr;
        }

    private:
        static bool s_Initialized;
        static uint32_t s_WindowCount;
        static int32_t s_GLVersionMajor;
        static int32_t s_GLVersionMinor;
    };
    bool GLFW::s_Initialized = false;
    uint32_t GLFW::s_WindowCount = 0;
    int32_t GLFW::s_GLVersionMajor = 0;
    int32_t GLFW::s_GLVersionMinor = 0;

	GlfwWindow::GlfwWindow(const WindowCreateInfo& info)
		: Window(info)
	{
#ifdef PULSARION_RENDERER_OPENGL
		m_Window = GLFW::NewWindow(m_Info);
        glfwMakeContextCurrent(m_Window);
#else
		m_Window = GLFW::NewNonApiWindow(info.Info);
#endif
        SetCallbacks();
	}

    GlfwWindow::~GlfwWindow()
    {
        GLFW::Shutdown(m_Window);
    }

    void GlfwWindow::OnUpdate()
	{
        glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

    bool GlfwWindow::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void GlfwWindow::SetVSync(bool enabled)
	{
        m_Info.VSync = enabled;
		glfwSwapInterval(enabled ? 1 : 0);
    }

    void GlfwWindow::SetFullscreen(bool enabled)
	{
	    PULSARION_ASSERT(false, "Not implemented!");
	}

    void GlfwWindow::SetTitle(const std::string& title)
    {
		glfwSetWindowTitle(m_Window, title.c_str());
    }

    void GlfwWindow::SetCallbacks()
    {
        glfwSetWindowUserPointer(m_Window, &m_Info);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
				WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
                // If Handler is null, then just return
                if (info.EventCallback == nullptr)
					return;
				info.Width = width;
				info.Height = height;

				WindowResizeEvent event(width, height);
				info.EventCallback(event);
			});

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
                if (info.EventCallback == nullptr)
					return;
                WindowCloseEvent event;
                info.EventCallback(event);
            });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
            {
				WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
				if (info.EventCallback == nullptr)
                    return;
				if (focused)
				{
					WindowFocusEvent event;
					info.EventCallback(event);
				}
				else
				{
					WindowLostFocusEvent event;
					info.EventCallback(event);
				}
			});

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
				WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
				if (info.EventCallback == nullptr)
                    return;
                    
                switch (action)
                {
                case GLFW_PRESS: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					info.EventCallback(event);
					break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    info.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					info.EventCallback(event);
					break;
				}
                }
            });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
                if (info.EventCallback == nullptr)
					return;
                KeyTypedEvent event(static_cast<KeyCode>(keycode));
				info.EventCallback(event);
            });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        	{
                WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
                if (info.EventCallback == nullptr)
                    return;

                switch (action)
                {
                case GLFW_PRESS: {
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					info.EventCallback(event);
					break;
                }
                case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					info.EventCallback(event);
					break;
				}
                }
            });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
            {
				WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
				if (info.EventCallback == nullptr)
					return;
				MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
				info.EventCallback(event);
			});

        glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered)
        	{
                WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
                if (info.EventCallback == nullptr)
					return;
                if (entered)
                {
                    MouseEnterEvent event;
                    info.EventCallback(event);
                }
                else
                {
					MouseLeaveEvent event;
					info.EventCallback(event);
				}
            });

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        	{
                WindowInfo& info = *static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
				if (info.EventCallback == nullptr)
                    return;
				MouseScrollEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
                info.EventCallback(event);
            });
    }

    std::shared_ptr<Window> CreateWindow(const WindowCreateInfo& info)
	{
		return std::make_shared<GlfwWindow>(info);
	}
}
