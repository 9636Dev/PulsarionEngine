#include "PulsarionCore/Log.hpp"
#include "PulsarionWindowing/Window.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    using namespace Pulsarion::Windowing;
    WindowCreationData creationData("Pulsarion Window", 800, 600, 0, 0, WindowFlags::DefaultNoVisible | WindowFlags::Resizable);
    auto window = CreateUniqueWindow(creationData);
    window->LimitEvents(argc == 2);

    window->SetOnClose([]() {
        PULSARION_LOG_INFO("Window close event received");
        return true;
    });

    // When the SetVisible method is called, the window will be shown and the OnWindowVisibility event will be triggered.
    window->SetOnWindowVisibility([](bool visible) {
        PULSARION_LOG_INFO("Window visibility event received: {}", visible ? "visible" : "hidden");
    });

    window->SetOnFocus([](bool focused) {
        PULSARION_LOG_INFO("Window focus event received: {}", focused ? "focused" : "unfocused");
    });

    window->SetOnResize([](int width, int height) {
        PULSARION_LOG_INFO("Window resize event received: {}x{}", width, height);
    });

    window->SetVisible(true);

    while (!window->ShouldClose())
    {
        PULSARION_LOG_INFO("New frame");
        window->PollEvents();
    }

    PULSARION_LOG_INFO("Window closed");

    return 0;
}
