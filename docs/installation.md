## Installation Guide

### Step 1: Clone the Repository

First, navigate to your project root and create an `external` directory to hold
third-party libraries. Next, clone the **Caitlyn** repository into this folder.

Open your terminal and run the following commands:

```shell
mkdir external
cd external
git clone https://github.com/szawrowski/caitlyn.git
```

### Step 2: Integrate Caitlyn into your CMake Project

Add the necessary configurations to the `CMakeLists.txt` file to link the
**Caitlyn** library to your project.

Use the following template as a reference:

```cmake
cmake_minimum_required(VERSION 3.10)
project(ProjectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the path to external dependencies
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/external/caitlyn")

# Find and include the Caitlyn package configuration
find_package(Caitlyn CONFIG REQUIRED)

# Create an executable target from main.cpp
add_executable(${PROJECT_NAME} main.cpp)

# Link the executable with Caitlyn library
target_link_libraries(${PROJECT_NAME} PRIVATE Caitlyn::Caitlyn)
```

Replace `ProjectName` with the actual name of your project and ensure `main.cpp`
is the source file for your main executable.

Run the simple program.

```c++
#include <caitlyn/io>

int main() {
  cait::println("Hello, world!");
  return 0;
}
```

To make your program work correctly on all platforms, you must initialize
application at the entry point.

```c++
int main() {
  const auto app = cait::application::init();
  // ...
}
```

Handling arguments and additional operations

```c++
int main(int argc, const char** argv) {
  const auto app = cait::application::init(argc, argv);
  
  // Get vector of arguments
  for (const auto& arg : app->get_args()) {
    cait::println("{} ", arg);
  }
  // Get system information
  cait::println("system name: {}", app->system_name());
}
```