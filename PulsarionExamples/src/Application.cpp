#include "PulsarionCore/Log.hpp"
#include "PulsarionWindowing/FrameLimiter.hpp"
#include "PulsarionWindowing/Window.hpp"
#include "PulsarionWindowing/WindowDebugger.hpp"

#include <chrono>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    using namespace Pulsarion::Windowing;
    constexpr DebugOptions options  = { false, true, true, true, true };
    WindowBounds bounds(0, 0, 1280, 720);
    WindowStyles styles = WindowStyles::NSTitled | WindowStyles::NSClosable | WindowStyles::NSMiniaturizable | WindowStyles::NSResizable;
    WindowConfig config;
    auto window = std::make_unique<DebugWindow<options, Window>>("Pulsarion Windowing", bounds, styles, config);
    window->SetVisible(true);

    FrameLimiter frameLimiter(240);
    auto start = std::chrono::high_resolution_clock::now();
    while (!window->ShouldClose())
    {
        frameLimiter.StartFrame();

        window->PollEvents();

        frameLimiter.EndFrame();
    }
    window = nullptr; // Destroy the window

    PULSARION_LOG_INFO("Window closed");

    return 0;
}
