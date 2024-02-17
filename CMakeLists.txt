cmake_minimum_required(VERSION 3.27)
project(PulsarionEngine VERSION 0.0.1 DESCRIPTION "A game engine written in C++")

set(PULSARION_ASM "NO" CACHE STRING "Choose whether to generate ASM")
set_property(CACHE PULSARION_ASM PROPERTY STRINGS "NO" "YES")

add_compile_definitions(
    $<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=0>
    $<$<CONFIG:Release>:SPDLOG_ACTIVE_LEVEL=1>
)

# If CMAKE_EXPORT_COMPILE_COMMANDS is enabled, make sure to not define header only for dependencies
if(NOT CMAKE_EXPORT_COMPILE_COMMANDS)
    set(PULSARION_MATH_HEADER_ONLY ON)
endif()

if (MSVC)
    # Suppress warnings from fmtlib
    add_compile_definitions(_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

    # Don't use header only, as that breaks IDE support for Visual Studio
    unset(PULSARION_MATH_HEADER_ONLY)
endif()

# Set Output Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (PULSARION_ASM STREQUAL "YES")
    MESSAGE(STATUS "Pulsarion: Enabling Assembly Output")
    if (CLANG OR GCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -S -fverbose-asm")
    elif (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FAs")
    endif()
endif()

# Pulsarion Dependencies
add_subdirectory(PulsarionCore)
add_subdirectory(PulsarionMath)
add_subdirectory(PulsarionMedia)
add_subdirectory(PulsarionWindowing)
add_subdirectory(PulsarionShaderLanguage)

add_subdirectory(PulsarionExamples)
add_subdirectory(PulsarionBenchmarks)

add_library(Pulsarion::Math ALIAS PulsarionMath)
add_library(Pulsarion::Core ALIAS PulsarionCore)
add_library(Pulsarion::Windowing ALIAS PulsarionWindowing)
add_library(Pulsarion::ShaderLanguage ALIAS PulsarionShaderLanguage)
add_library(Pulsarion::Media ALIAS PulsarionMedia)
