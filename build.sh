#!/bin/bash

# Check if an argument is provided and validate it
if [[ "$#" -eq 1 ]]; then
  # Convert the argument to lowercase
  build_type=$(echo "$1" | tr '[:upper:]' '[:lower:]')

  # Check if the provided argument is either Release or Debug
  if [ $build_type == "release" ]; then
    build_type="Release"
  elif [ $build_type == "debug" ]; then
    build_type="Debug"
  else
    echo "Error: Invalid build type '$build_type'."
    echo "Please specify either 'Release' or 'Debug'."
    exit 1
  fi
elif [ "$#" -eq 0 ]; then
  # If no arguments are provided, set build type to Debug
  build_type="Debug"
fi

# Build type message
echo "Build type: $build_type"

# Set build directory
build_dir="build/$build_type/"

# Run cmake with the appropriate build type
cmake -S . -B $build_dir -G "Ninja" -DCMAKE_BUILD_TYPE=$build_type

# Build the targets
cmake --build $build_dir --parallel 4

# Run tests
test_dir="$build_dir/test/"
ctest --test-dir $test_dir --build-config Debug --output-on-failure --parallel 4
