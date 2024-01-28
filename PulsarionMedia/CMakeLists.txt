cmake_minimum_required(VERSION 3.27)
project(PulsarionMedia VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "Pulsarion Multi-Media Library")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_MEDIA_SOURCES
    src/PulsarionMedia/Core.hpp
    src/PulsarionMedia/StbImageImpl.cpp
    src/PulsarionMedia/Image.hpp
    src/PulsarionMedia/Image.cpp
)

if (NOT DEFINED PULSARION_LIBRARY_TYPE)
    message(FATAL_ERROR "PULSARION_LIBRARY_TYPE is not defined, please include PulsarionCore first!")
    return()
endif()

add_library(PulsarionMedia ${PULSARION_LIBRARY_TYPE} ${PULSARION_MEDIA_SOURCES})

if (PULSARION_LIBRARY_TYPE STREQUAL "SHARED")
    target_compile_definitions(PulsarionMedia PUBLIC PULSARION_MEDIA_BUILD_DLL)
endif()

target_include_directories(PulsarionMedia PUBLIC src)
target_include_directories(PulsarionMedia PUBLIC vendor/stb)

add_dependencies(PulsarionMedia Pulsarion::Core)
target_link_libraries(PulsarionMedia PUBLIC Pulsarion::Core)
