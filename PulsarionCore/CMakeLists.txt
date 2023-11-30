cmake_minimum_required(VERSION 3.27)
project(PulsarionCore)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_DESCRIPTION "This project contains the core headers and loggers used by Pulsarion")

if(NOT DEFINED PULSARION_LIBRARY_TYPE)
    set(PARENT_SCOPE PULSARION_LIBRARY_TYPE "STATIC" CACHE STRING "Type of library to build, static or shared")
endif()
MESSAGE(NOTICE "Building Pulsarion for type: ${PULSARION_LIBRARY_TYPE}")

add_subdirectory(vendor/spdlog) # SpdLog

set(PULSARION_BUILD_LIBRARY_DEFINE STRING "PULSARION_BUILD_DLL")

set(PULSARION_CORE_SOURCES
    src/PulsarionCore/Log.hpp
    src/PulsarionCore/Log.cpp
        src/PulsarionCore/Core.hpp
        src/PulsarionCore/Core.hpp
        src/PulsarionCore/Assert.hpp
)
add_library(PulsarionCore STATIC ${PULSARION_CORE_SOURCES})

if (PULSARION_LIBRARY_TYPE STREQUAL "STATIC")
    target_compile_definitions(PulsarionCore PUBLIC "PULSARION_BUILD_STATIC_LIB")
elseif (PULSARION_LIBRARY_TYPE STREQUAL "SHARED")
    target_compile_definitions(PulsarionCore PUBLIC "PULSARION_BUILD_SHARED_LIB")
endif()

target_compile_definitions(PulsarionCore PUBLIC
        $<$<PLATFORM_ID:Windows>:PULSARION_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:PULSARION_PLATFORM_LINUX>
        $<$<PLATFORM_ID:Darwin>:PULSARION_PLATFORM_MACOS>
        $<$<CONFIG:Debug>:PULSARION_DEBUG>
        $<$<CONFIG:Release>:PULSARION_RELEASE>
        $<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=0>
)

target_link_libraries(PulsarionCore PUBLIC spdlog::spdlog)

target_include_directories(PulsarionCore PUBLIC src)
