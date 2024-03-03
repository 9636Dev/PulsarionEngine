#include <benchmark/benchmark.h>
#include "PulsarionMath/Vector.hpp"

static void BM_PulsarionPackedVec4_Multiply(benchmark::State& state)
{
    auto a = Pulsarion::Math::Vector<4, float, Pulsarion::Math::Qualifier::Packed>(1.0f);
    auto b = Pulsarion::Math::Vector<4, float, Pulsarion::Math::Qualifier::Packed>(1.0f);
    for (auto _ : state) {
        benchmark::DoNotOptimize(a * b);
    }
}

BENCHMARK(BM_PulsarionPackedVec4_Multiply);

static void BM_PulsarionAlignedVec4_Multiply(benchmark::State& state)
{
    auto a = Pulsarion::Math::Vector<4, float, Pulsarion::Math::Qualifier::Aligned>(1.0f);
    auto b = Pulsarion::Math::Vector<4, float, Pulsarion::Math::Qualifier::Aligned>(1.0f);
    for (auto _ : state) {
        benchmark::DoNotOptimize(a * b);
    }
}

BENCHMARK(BM_PulsarionAlignedVec4_Multiply);
