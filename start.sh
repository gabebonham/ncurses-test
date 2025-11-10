#!/bin/bash
set -e

BUILD_DIR="build"
SOURCE_FILE="main.c"
COMPILED_FILE="main"
OUTPUT_FILE="./${BUILD_DIR}/${COMPILED_FILE}"

# Handle "clean"
if [[ "$1" == "clean" ]]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    exit 0
fi

# Create build directory if missing
mkdir -p "$BUILD_DIR"

# Build type detection
if [[ "$1" == "--release" ]]; then
    echo "Building in release mode..."
    CFLAGS="-Wall -Wextra -O2"
else
    echo "Building in debug mode..."
    CFLAGS="-Wall -Wextra -g"
fi

# Compile
# echo "Compiling project..."
# gcc $CFLAGS ./*.c ./ui/*.c ./utils/*.c -o "$OUTPUT_FILE" -lncurses
# echo "Build successful: $OUTPUT_FILE"

# Run binary with remaining args
"$OUTPUT_FILE" "${@:2}"
