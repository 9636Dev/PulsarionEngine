#include "PulsarionCore/Log.hpp"
#include "PulsarionWindowing/Window.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    using namespace Pulsarion::Windowing;
    WindowCreationData creationData("Pulsarion Window", 800, 600);
    auto window = CreateUniqueWindow(creationData);
    window->SetVisible(true);

    while (!window->ShouldClose())
    {
        window->PollEvents();
    }

    PULSARION_LOG_INFO("Window closed");

    return 0;
}
