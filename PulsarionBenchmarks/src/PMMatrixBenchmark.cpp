#include <benchmark/benchmark.h>

#include "PulsarionMath/Matrix.hpp"

static void BM_PMMatrixTranspose(benchmark::State& state) {
    Pulsarion::Math::Matrix<4, 4, float> matrix;

    for (auto _ : state) {
        benchmark::DoNotOptimize(matrix.Transpose());
    }
}

BENCHMARK(BM_PMMatrixTranspose);

static void BM_PMMatrixMultiply(benchmark::State& state) {
    Pulsarion::Math::Matrix<4, 4, float> left;
    Pulsarion::Math::Matrix<4, 4, float> right;

    for (auto _ : state) {
        benchmark::DoNotOptimize(Pulsarion::Math::MatrixFunctions<4, 4, float>::Multiply(left, right));
    }
}

BENCHMARK(BM_PMMatrixMultiply);
