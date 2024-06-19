#!/bin/bash

root=$(pwd)

# Check if vcpkg is installed
if [[ ! -d "$HOME/vcpkg" ]]; then
  echo "vcpkg is not installed."
  echo "Installing vcpkg..."

  cd $HOME
  # Download vcpkg using Git
  git clone https://github.com/microsoft/vcpkg.git
  # Run the vcpkg installation
  cd vcpkg/
  ./bootstrap-vcpkg.sh

  echo "vcpkg was successfully installed."
fi

# Installing dependencies

# Change to the vcpkg directory
cd "$HOME/vcpkg/"

# Detecting platform and operating system
platform=$(uname -m)
os=$(uname -s)

echo "Current architecture: $platform"
echo "Current operating system: $os"

if [[ "$platform" == "x86_64" ]]; then
  if [[ "$os" == "Linux" ]]; then
    triplet="x64-linux"
  elif [[ "$os" == "Darwin" ]]; then
    triplet="x64-osx"
  else
    echo "Unsupported operating system: $os"
    exit 1
  fi
elif [[ "$platform" == "aarch64" ]]; then
  if [[ "$os" == "Linux" ]]; then
    triplet="arm64-linux"
  else
    echo "Unsupported operating system: $os"
    exit 1
  fi
else
  echo "Unsupported platform: $platform"
  exit 1
fi

# Set config
config="$root/depends.conf"

# Check if the config exists
if [[ ! -f "$config" ]]; then
  echo "Error: $config does not exist."
  exit 1
fi

# Read the config
libs="$(echo $(cat "$config") | tr '\n' ' ' | sed 's/ *$//')"

# Installing dependencies
./vcpkg install $libs --triplet=$triplet
