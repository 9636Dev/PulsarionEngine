#!/bin/sh
#
# Build the project, if argument is 'compile_commands' then generate compile_commands.json
# Usage: build_project.sh [compile_commands]

GENERATOR="Unix Makefiles"
BUILD_DIR=".."
BUILD_TYPE="Debug"
LIBRARY_TYPE="SHARED"
GENERATE_COMPILE_COMMANDS=

# Make sure current dir is the script dir
cd "$(dirname "$0")"


if [ "$1" = "compile_commands" ]; then
    GENERATE_COMPILE_COMMANDS=-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fi

cmake -G "$GENERATOR" -DPULSARION_LIBRARY_TYPE="$LIBRARY_TYPE" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" "$GENERATE_COMPILE_COMMANDS" "$BUILD_DIR"
