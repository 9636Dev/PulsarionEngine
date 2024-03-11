#include "PulsarionCore/File.hpp"
#define PULSARION_EXAMPLES_SHADER_LANGUAGE
#ifdef PULSARION_EXAMPLES_WINDOWING
#include "PulsarionCore/Log.hpp"
#include "PulsarionWindowing/FrameLimiter.hpp"
#include "PulsarionWindowing/Window.hpp"
#include "PulsarionWindowing/WindowDebugger.hpp"

#include <chrono>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    using namespace Pulsarion::Windowing;
    expr DebugOptions options = {false, true, true, true, true};
    WindowBounds bounds(0, 0, 1280, 720);
    WindowStyles styles = WindowStyles::NSTitled | WindowStyles::NSClosable | WindowStyles::NSMiniaturizable |
                          WindowStyles::NSResizable;
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

    PULSARION_LOG_INFO("Window closed");
    window = nullptr; // Destroy the window
    PULSARION_LOG_INFO("Window destroyed");
    return 0;
}
#elif defined(PULSARION_EXAMPLES_SHADER_LANGUAGE)
#endif
#include "PulsarionCore/Log.hpp"
#include "PulsarionShaderLanguage/Lexer.hpp"
#include "PulsarionShaderLanguage/Parser.hpp"
#include "PulsarionShaderLanguage/Preprocessor.hpp"
#include "PulsarionShaderLanguage/TypeCheck.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    using namespace Pulsarion::Shader;
    std::string path = "resources/shaders/lexer_test.pshl";
    std::string beforePreprocess = Pulsarion::File::ReadAllText(path);
    PULSARION_LOG_INFO("Before preprocess: {}", beforePreprocess);
    auto res = Preprocessor(beforePreprocess, path).Process();
    if (res.HasError())
    {
        PULSARION_LOG_ERROR("Preprocessing failed: {0}:{1} - {2}", res.Path.string(), res.Line,
                            Preprocessor::ErrorToString(res.Err));
        return 1;
    }
    auto source = std::move(res.Source);
    PULSARION_LOG_INFO("After preprocess: {}", source);
    Parser parser(Lexer{source});
    auto result = parser.Parse();

    // Display warnings regardless of success
    for (auto &warning: result.Warnings)
    {
        PULSARION_LOG_WARN("[{0}] {1}", Parsing::Error::SourceToString(warning.Source),
                           Parsing::Error::TypeToString(warning.Type));
    }

    if (result.Success())
    {
        PULSARION_LOG_INFO("Parsed with no errors");
        PULSARION_ASSERT(result.Root.has_value(), "Root node is missing");
        auto ast = result.Root.value();
        PULSARION_LOG_DEBUG("AST: {}", ast.ToString());

        TypeChecker typeChecker(std::move(ast));
        typeChecker.GenerateTypeInformation();
    } else
    {
        PULSARION_LOG_ERROR("Parsing failed");

        for (auto &error: result.Errors)
        {
            PULSARION_LOG_ERROR("[{0}] {1}", Parsing::Error::SourceToString(error.Source),
                                Parsing::Error::TypeToString(error.Type));
        }
    }

    return 0;
}
