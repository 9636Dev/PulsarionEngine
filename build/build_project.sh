#!/bin/sh
#
# Build the project, if argument is 'compile_commands' then generate compile_commands.json
# Usage: build_project.sh [compile_commands]

GENERATOR="Unix Makefiles"
BUILD_DIR=".."
BUILD_TYPE="Debug"
LIBRARY_TYPE="SHARED"
COMPILE_COMMANDS=false
SIMD="SSE4.1"

# Make sure current dir is the script dir
cd "$(dirname "$0")"

# If arguments contain 'compile_commands' then generate compile_commands.json
for arg in "$@"; do
    if [ "$arg" = "compile_commands" ]; then
        COMPILE_COMMANDS=true
    fi

    if [ "$arg" = "release" ]; then
        BUILD_TYPE="Release"
    fi

    if [ "$arg" = "static" ]; then
        LIBRARY_TYPE="STATIC"
    fi

    if [ "$arg" = "simd_avx" ]; then
        SIMD="AVX"
    fi

    if [ "$arg" = "simd_none" ]; then
        SIMD="None"
    fi
done

if [ "$BUILD_TYPE" = "Release" ]; then
    echo "Building release"
fi

if [ $COMPILE_COMMANDS ]; then
    echo "Generating compile_commands.json"
    cmake -G "$GENERATOR" -DPULSARION_LIBRARY_TYPE="$LIBRARY_TYPE" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DPULSARION_SIMD="$SIMD" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON  "$BUILD_DIR"
else
    cmake -G "$GENERATOR" -DPULSARION_LIBRARY_TYPE="$LIBRARY_TYPE" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DPULSARION_SIMD="$SIMD" "$BUILD_DIR"
fi


if [ $COMPILE_COMMANDS ]; then
    # Move compile_commands.json to project root
    mv compile_commands.json ../
fi
