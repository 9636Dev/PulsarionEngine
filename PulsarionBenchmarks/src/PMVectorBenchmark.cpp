#include <benchmark/benchmark.h>
#include "PulsarionMath/Vector/PackedVec4.hpp"

static void BM_PulsarionPackedVec4_Multiply(benchmark::State& state)
{
    auto a = Pulsarion::Math::Vector<4, float, Pulsarion::Math::Qualifier::Packed>(1.0f);
    auto b = Pulsarion::Math::Vector<4, float, Pulsarion::Math::Qualifier::Packed>(1.0f);
    for (auto _ : state) {
        benchmark::DoNotOptimize(a * b);
    }
}

BENCHMARK(BM_PulsarionPackedVec4_Multiply);
