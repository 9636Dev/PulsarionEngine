#include <benchmark/benchmark.h>
#define PULSARION_MATH_DISABLE_SIMD
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

static void BM_Vector2f_Add(benchmark::State& state) {
	Vec2f a(1.0f, 2.0f);
	Vec2f b(3.0f, 4.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a + b);
	}
}

// TODO: Add more benchmarks

BENCHMARK(BM_Vector2f_Add);

static void BM_Vector4f_Multiply(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4f b(5.0f, 6.0f, 7.0f, 8.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a * b);
	}
}

BENCHMARK(BM_Vector4f_Multiply);

static void BM_Vector4f_Dot(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4f b(5.0f, 6.0f, 7.0f, 8.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a.Dot(b));
	}
}

BENCHMARK(BM_Vector4f_Dot);

static void BM_Vector4f_Cross(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4f b(5.0f, 6.0f, 7.0f, 8.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a.Cross3D(b));
	}
}

BENCHMARK(BM_Vector4f_Cross);

static void BM_Vector4f_Normalize(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a.Normalize());
	}
}

BENCHMARK(BM_Vector4f_Normalize);

// Basically same as normalize, but without the division
static void BM_Vector4f_InverseMagnitudeLowP(benchmark::State& state) {
	Vec4f a(1.0f, 2.0f, 3.0f, 4.0f);
	for (auto _ : state) {
		benchmark::DoNotOptimize(a.InverseMagnitudeLowP());
	}
}

BENCHMARK(BM_Vector4f_InverseMagnitudeLowP);
