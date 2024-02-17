cmake_minimum_required(VERSION 3.27)
project(PulsarionBenchmarks)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch Google Benchmark
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.5.2  # Optionally specify a version tag or commit
)
# Set benchmark_ENABLE_TESTING to OFF to avoid Google Benchmark's own tests being run
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

FetchContent_MakeAvailable(googlebenchmark)
# Suppress warnings from Google Benchmark
target_compile_options(benchmark PRIVATE -w)

set(PULSARION_BENCHMARK_SOURCE
    src/VectorBenchmark.cpp
    src/VectorSimdBenchmark.cpp
    src/MatrixBenchmark.cpp
    src/MatrixSimdBenchmark.cpp
    src/LexerBenchmark.cpp
    src/Benchmark.cpp
    # GLM
    src/GLMMatrixBenchmark.cpp
)
add_executable(PulsarionBenchmarks ${PULSARION_BENCHMARK_SOURCE})

add_subdirectory(vendor/glm)
target_link_libraries(PulsarionBenchmarks glm) # We want to benchmark glm as well

target_link_libraries(PulsarionBenchmarks PulsarionMath)
target_link_libraries(PulsarionBenchmarks PulsarionShaderLanguage)

target_link_libraries(PulsarionBenchmarks benchmark::benchmark)
