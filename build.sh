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
  elif [ $build_type == "install" ]; then
    install="true"
  else
    echo "Error: Invalid build type '$build_type'."
    echo "Please specify either 'Release' or 'Debug'."
    exit 1
  fi
elif [ "$#" -eq 0 ]; then
  # If no arguments are provided, set build type to Debug
  build_type="Debug"
  install="false"
fi

# Set build directory
build_dir="build/$build_type/"

if [ $install == "true" ]; then
  # Build type message
  echo "Installation..."

  cmake -S . -B $build_dir -DLIB_INSTALL=ON
  cmake --install $build_dir
else
  # Build type message
  echo "Build type: $build_type"

  # Run cmake with the appropriate build type
  cmake -S . -B $build_dir -G "Ninja" -DCMAKE_BUILD_TYPE=$build_type -DDEVELOPMENT=ON

  # Build the targets
  cmake --build $build_dir --parallel 16

  # Run tests
  test_dir="$build_dir/test/"
  ctest --test-dir $test_dir --build-config Debug --output-on-failure --parallel 16
fi
