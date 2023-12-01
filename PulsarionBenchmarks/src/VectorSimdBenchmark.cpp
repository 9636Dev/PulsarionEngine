#include <benchmark/benchmark.h>
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

static void BM_SimdVector4f_Multiply(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4f b(5.0f, 6.0f, 7.0f, 8.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a * b);
	}
}

BENCHMARK(BM_SimdVector4f_Multiply);

static void BM_SimdVector4f_Dot(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4f b(5.0f, 6.0f, 7.0f, 8.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a.Dot(b));
	}
}

BENCHMARK(BM_SimdVector4f_Dot);

static void BM_SimdVector4f_Cross(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4f b(5.0f, 6.0f, 7.0f, 8.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a.Cross3D(b));
	}
}

BENCHMARK(BM_SimdVector4f_Cross);