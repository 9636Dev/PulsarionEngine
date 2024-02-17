#include <benchmark/benchmark.h>

#include <glm/glm.hpp>

static void BM_GLMMat4_Multiply(benchmark::State& state)
{
    glm::mat4 a(1.0f);
    glm::mat4 b(1.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a * b);
	}
}

BENCHMARK(BM_GLMMat4_Multiply);

