cmake_minimum_required(VERSION 3.27)
project(PulsarionBenchmarks)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set benchmark_ENABLE_TESTING to OFF to avoid Google Benchmark's own tests being run
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(vendor/benchmark)
add_subdirectory(vendor/glm)

target_compile_options(benchmark PRIVATE -w)

# Suppress warnings from Google Benchmark

set(PULSARION_BENCHMARK_SOURCE
    src/Benchmark.cpp
    # GLM
    src/GLMVectorBenchmark.cpp
    src/GLMMatrixBenchmark.cpp

    # Pulsarion Math
    src/PMVectorBenchmark.cpp

    # Pulsarion Shader Language
    src/PSLLexerBenchmark.cpp
)
add_executable(PulsarionBenchmarks ${PULSARION_BENCHMARK_SOURCE})

add_dependencies(PulsarionBenchmarks benchmark glm)
add_dependencies(PulsarionBenchmarks PulsarionMath)
add_dependencies(PulsarionBenchmarks PulsarionShaderLanguage)
add_dependencies(PulsarionBenchmarks benchmark::benchmark)

target_link_libraries(PulsarionBenchmarks glm) # We want to benchmark glm as well
target_link_libraries(PulsarionBenchmarks PulsarionMath)
target_link_libraries(PulsarionBenchmarks PulsarionShaderLanguage)
target_link_libraries(PulsarionBenchmarks benchmark::benchmark)
