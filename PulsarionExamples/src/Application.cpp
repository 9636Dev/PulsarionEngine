#include "PulsarionCore/Assert.hpp"
#include "PulsarionCore/Log.hpp"

#include "PulsarionWindowing/Window.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    PULSARION_ASSERT(argc == 1, "argc must be 1");
    PULSARION_RUN_IF_DEBUG(PULSARION_LOG_DEBUG("Hello from Debug!"));
    PULSARION_LOG_INFO("Hello, PulsarionCore!");

    auto window = Pulsarion::Windowing::CreateWindow(Pulsarion::Windowing::WindowCreateInfo());
    window->SetEventCallback([](const Pulsarion::Windowing::Event& event)
        {
		PULSARION_LOG_TRACE(event.ToString());
	});

    while (!window->ShouldClose())
    {
        window->OnUpdate();
    }

    return 0;
}