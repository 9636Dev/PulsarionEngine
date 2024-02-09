#!/bin/sh
#
# Build the project, if argument is 'compile_commands' then generate compile_commands.json
# Usage: build_project.sh [compile_commands]

GENERATOR="Unix Makefiles"
BUILD_DIR=".."
BUILD_TYPE="Debug"
LIBRARY_TYPE="SHARED"

# Make sure current dir is the script dir
cd "$(dirname "$0")"


if [ "$1" = "compile_commands" ]; then
    echo "Generating compile_commands.json"
    cmake -G "$GENERATOR" -DPULSARION_LIBRARY_TYPE="$LIBRARY_TYPE" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" "$BUILD_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
else
    cmake -G "$GENERATOR" -DPULSARION_LIBRARY_TYPE="$LIBRARY_TYPE" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" "$BUILD_DIR"
fi


if [ "$1" = "compile_commands" ]; then
    # Move compile_commands.json to project root
    mv compile_commands.json ../
fi
