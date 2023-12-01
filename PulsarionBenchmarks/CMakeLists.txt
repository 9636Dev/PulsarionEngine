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
set(benchmark_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

set(PULSARION_BENCHMARK_SOURCE
    src/VectorBenchmark.cpp
    src/VectorSimdBenchmark.cpp
    src/MatrixBenchmark.cpp
    src/MatrixSimdBenchmark.cpp
    src/Benchmark.cpp
)
add_executable(PulsarionBenchmarks ${PULSARION_BENCHMARK_SOURCE})

# Make sure to link PulsarionMath
target_link_libraries(PulsarionBenchmarks PulsarionMath)

target_link_libraries(PulsarionBenchmarks benchmark::benchmark)
