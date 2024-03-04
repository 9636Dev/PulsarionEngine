#include <benchmark/benchmark.h>
#include <glm/glm.hpp>

static void BM_GLMVec4_Multiply(benchmark::State& state)
{
    glm::vec4 a(1.0f);
    glm::vec4 b(1.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a * b);
	}
}

BENCHMARK(BM_GLMVec4_Multiply);

static void BM_GLMVec4_Dot(benchmark::State& state)
{
    glm::vec4 a(1.0f);
    glm::vec4 b(1.0f);
    for (auto _ : state) {
        benchmark::DoNotOptimize(glm::dot(a, b));
    }
}

BENCHMARK(BM_GLMVec4_Dot);
