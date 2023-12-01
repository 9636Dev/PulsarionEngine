cmake_minimum_required(VERSION 3.27)
project(PulsarionProject)

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

# PulsarionCore Dependencies
add_subdirectory(PulsarionCore)
add_subdirectory(PulsarionMath)

add_subdirectory(PulsarionTests)
add_subdirectory(PulsarionExamples)

add_library(Pulsarion::Math ALIAS PulsarionMath)
add_library(Pulsarion::Core ALIAS PulsarionCore)
