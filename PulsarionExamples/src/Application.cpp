#include "PulsarionCore/Log.hpp"
#include "PulsarionWindowing/FrameLimiter.hpp"
#include "PulsarionWindowing/Window.hpp"
#include "PulsarionWindowing/WindowDebugger.hpp"

#include <chrono>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    using namespace Pulsarion::Windowing;
    WindowFlags flags = WindowFlags::DefaultNoVisible | WindowFlags::Resizable;
    WindowCreationData creationData("Pulsarion Window", 800, 600, 0, 0, flags);
    //auto window = CreateUniqueWindow(creationData);
    constexpr DebugOptions options  = { false, true, false, true, true };
    auto window = std::make_unique<DebugWindow<options>>(creationData);
    window->SetVisible(true);

    FrameLimiter frameLimiter(240);
    auto start = std::chrono::high_resolution_clock::now();
    while (!window->ShouldClose())
    {
        frameLimiter.StartFrame();

        window->PollEvents();

        frameLimiter.EndFrame();
    }

    PULSARION_LOG_INFO("Window closed");

    return 0;
}
