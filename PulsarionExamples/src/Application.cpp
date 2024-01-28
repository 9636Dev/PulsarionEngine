#include "PulsarionCore/Assert.hpp"
#include "PulsarionCore/Log.hpp"

#include "PulsarionWindowing/Window.hpp"

#include "PulsarionShaderLanguage/Lexer.hpp"
#include "PulsarionShaderLanguage/Parser.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    PULSARION_ASSERT(argc == 1, "argc must be 1");
    PULSARION_RUN_IF_DEBUG(PULSARION_LOG_DEBUG("Hello from Debug!"));
    PULSARION_LOG_INFO("Hello, PulsarionCore!");
    PULSARION_LOG_INFO("SpdLog Level: {}", SPDLOG_ACTIVE_LEVEL);

    using namespace Pulsarion::Shader;

    Lexer lexer(Pulsarion::File::ReadAllText("resources/shaders/lexer_test.pshl"));
    Parser parser(std::move(lexer));
    auto result = parser.Parse();

    if (result.Errors.size() > 0)
    {
        for (const auto& error : result.Errors)
        {
            PULSARION_LOG_ERROR("[{0}:{1}] {2} {3}", error.Location.Line, error.Location.Column, SeverityToString(error.Severity), error.Message);
        }
    }
    else
    {
        PULSARION_ASSERT(result.Root.has_value(), "Root node must have a value when there are no errors!");
        PULSARION_LOG_INFO("{}", result.Root->ToString());

        PULSARION_LOG_INFO("Parsed with no errors!");
    }

    /*
    auto window = Pulsarion::Windowing::CreateWindow(Pulsarion::Windowing::WindowCreateInfo());
    window->SetEventCallback([](const Pulsarion::Windowing::Event& event)
    {
        PULSARION_LOG_TRACE(event.ToString());
    });
    window->SetTitle("Pulsarion Engine");
    window->SetCursorShape(Pulsarion::Windowing::StandardCursorShape::Hand);

    while (!window->ShouldClose())
    {
        window->OnUpdate();
    }
    */
    return 0;
}
