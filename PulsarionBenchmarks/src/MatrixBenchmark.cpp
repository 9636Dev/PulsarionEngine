#include <benchmark/benchmark.h>
#define PULSARION_MATH_DISABLE_SIMD
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

static void BM_Mat4_Multiply(benchmark::State& state)
{
	Mat4 a(1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			 13.0f, 14.0f, 15.0f, 16.0f);
	Mat4 b(17.0f, 18.0f, 19.0f, 20.0f,
		    21.0f, 22.0f, 23.0f, 24.0f,
			25.0f, 26.0f, 27.0f, 28.0f,
			29.0f, 30.0f, 31.0f, 32.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a * b);
	}
}

BENCHMARK(BM_Mat4_Multiply);

static void BM_Mat4_VecMultiply(benchmark::State& state)
{
	Mat4 a(1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f);

	Vec4 b(17.0f, 18.0f, 19.0f, 20.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a * b);
	}
}

BENCHMARK(BM_Mat4_VecMultiply);