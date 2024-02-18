#include "PulsarionCore/Assert.hpp"
#include "PulsarionCore/Log.hpp"

#include "PulsarionShaderLanguage/ParserUtil.hpp"
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

    if (!result.Errors.empty())
    {
        // Sort the error by increasing nesting level, since the least nested errors are the most important (probably)
        result.Errors.sort([](const Parsing::Error& a, const Parsing::Error& b)
        {
            return a.NestingLevel < b.NestingLevel;
        });

        for (const auto& error : result.Errors)
        {
            PULSARION_LOG_ERROR("[{0}:{1}] {2} {3} {4} {5}", error.Location.Line, error.Location.Column,
                SeverityToString(error.Severity), Parsing::Error::SourceToString(error.Source),
                error.NestingLevel, Parsing::Error::TypeToString(error.Type));
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
    }*/
    return 0;
}
