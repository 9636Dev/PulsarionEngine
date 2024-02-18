#include <benchmark/benchmark.h>
#include <array>

#include <PulsarionShaderLanguage/Lexer.hpp>

static const std::array<std::string, 16> NUMBERS = {
    "1234",
    "0x1f3f",
    "0b101010",
    "0o123",
    "1234.5678",
    "1.5e3",
    "1.5e-3",
    "1.5e+3",
    "100u",
    "100U",
    "100l",
    "100L",
    "100ul",
    "100UL",
    "100ull",
    "100ULL"
};

using namespace Pulsarion::Shader;

static void BM_Lexer_LexNumber(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::string source;
        // Dynamically generate the string based on the state range
        for (std::size_t i = 0; i < static_cast<std::size_t>(state.range(0)); ++i) {
            source += NUMBERS[i % NUMBERS.size()];
            source += " ";
        }
        state.ResumeTiming();

        Lexer lexer(source);
        while (!lexer.IsEnd()) {
            lexer.NextToken();
        }
    }
    // Optionally, set the complexity based on the input size
    state.SetComplexityN(state.range(0));
}

// Register the function as a benchmark with a range of inputs
BENCHMARK(BM_Lexer_LexNumber)->RangeMultiplier(2)->Range(1<<10, 1<<15);

static void BM_Lexer_LexIdentifier(benchmark::State& state) {
    static std::string source;
    if (source.empty()) {
        //state.PauseTiming(); // We need to generate the string
        // Generate the string
        for (std::size_t i = 0; i < 1000; ++i) {
            source += "identifier ";
        }
        //state.ResumeTiming();
    }

    for (auto _ : state) {
        Lexer lexer(source);
        while (!lexer.IsEnd()) {
            lexer.NextToken();
        }
    }
}

BENCHMARK(BM_Lexer_LexIdentifier);
