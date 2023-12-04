#include "PulsarionCore/Assert.hpp"
#include "PulsarionCore/Log.hpp"

#include "PulsarionWindowing/Window.hpp"

#include "PulsarionShaderLanguage/Lexer.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    PULSARION_ASSERT(argc == 1, "argc must be 1");
    PULSARION_RUN_IF_DEBUG(PULSARION_LOG_DEBUG("Hello from Debug!"));
    PULSARION_LOG_INFO("Hello, PulsarionCore!");
    PULSARION_LOG_INFO("SpdLog Level: {}", SPDLOG_ACTIVE_LEVEL);

    Pulsarion::Shader::Lexer lexer(Pulsarion::File::ReadAllText("resources/shaders/lexer_test.pshl"));
    Pulsarion::Shader::Token token = lexer.NextToken();
    do
    {
        token = lexer.NextToken();
        PULSARION_LOG_INFO("Token: {}, '{}', {}:{}", Pulsarion::Shader::TokenToString(token.Type), token.Value, token.Line, token.Column);
    } while (token.Type != Pulsarion::Shader::TokenType::EndOfFile);

    std::exit(0); // TODO: Remove this after shader testing

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
