# Caitlyn

## About

**Caitlyn** is a header-only versatile general-purpose C++ library designed to
enhance productivity for everyday tasks.

## Features

### Caitlyn includes
- [Unicode String Handling](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#unicode-strings-support)
- [Text Formatting](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#text-formatting)
- [File Management](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#file-management)
- [Serializing](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#serializing)
- [Error Handling](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#error-handling)
- [Numeric](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#numeric)
- [Type Traits](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#type-traits)
- [Unit Testing](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#unit-testing)
- [Utilities](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#utilities)

Supported Platforms: **Linux, Windows, macOS**\
Supported Standard: **C++11** or later

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
find_package(caitlyn CONFIG REQUIRED)

# Create an executable target from main.cpp
add_executable(${PROJECT_NAME} main.cpp)

# Link the executable with Caitlyn library
target_link_libraries(${PROJECT_NAME} PRIVATE Caitlyn::Caitlyn)
```

Replace `ProjectName` with the actual name of your project and ensure `main.cpp`
is the source file for your main executable.

Run the simple program.

```c++
#include <caitlyn/core/io.h>

int main() {
  cait::println("Hello, world!");
  return 0;
}
```

## Examples

### Unicode Strings Support

You can continue using standard C++ strings, supplemented with Unicode wrappers.

- `unichar_t`: Wrapper for Unicode code point characters.
- `unistring_t`: String wrapper based on Unicode code points with iterator
   support.

**Usage**

```c++
#include <caitlyn/core/io.h>
#include <caitlyn/core/string.h>

int main() {
  const auto string = "Hello, 世界!"_str;
  const auto emoji = "🙂"_char;

  cait::println("{} {}", string, emoji);
  return 0;
}
```

```text
Hello, 世界! 🙂
```

### Text Formatting

- `text_t`: - String builder type.
- `format`: - Universal string formatter.

**Usage**

```c++
#include <caitlyn/core/io.h>
#include <caitlyn/core/text.h>

int main() {
  const auto string = "Hello, 世界!";
  const auto emoji = "🙂";

  const auto formatted = cait::format("{} {}", string, emoji);

  auto content = cait::make_text("Text: ");
  content.append("Lorem ipsum dolor sit amet, ");
  content.append_line("consectetur adipiscing elit...");
  content.append_line(formatted);

  cait::println(content);
  return 0;
}
```

```text
Text: Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, 世界! 🙂
```

### File Management

- `file_t`: Universal file handler.

**Usage**

- Write text to file

```c++
#include <caitlyn/core/file.h>

int main() {
  const auto some = "Lorem ipsum dolor sit amet,";
  const auto other = "consectetur adipiscing elit...";
  const auto unicode = "Hello, 世界!";

  auto file = "somefile.txt"_file;
  file.write("{} {}\n{}", some, other, unicode);
  file.close();
  
  return 0;
}
```

- File (_somefile.txt_)

```text
Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, 世界!
```

- Read lines from file

```c++
#include <caitlyn/core/file.h>
#include <caitlyn/core/io.h>

int main() {
  auto file = "somefile.txt"_file;

  while (file) {
    cait::println("{}", file.read_line());
  }
  return 0;
}
```

```text
Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, 世界!
```

### Serializing

#### JSON

The JSON format is crucial for web development, API integration, and any
applications that need efficient data exchange in a structured format.

- `json_t`: Provides comprehensive support for JSON handling.
  Facilitates parsing, generating, and manipulating JSON data structures.
  Enables easy serialization of complex data into JSON format for storage or
  transmission, and deserialization of JSON back into native data structures.
  Offers efficient methods for encoding and decoding JSON, handling nested
  objects and arrays, ensuring compatibility across various platforms and
  systems.

**Usage**

- Brackets operator

```c++
#include <caitlyn/core/io.h>
#include <caitlyn/ser/json.h>

int main() {
  auto config = cait::make_json();
  config["name"] = cait::json::make_object();
  config["name"]["first"] = "John";
  config["name"]["last"] = "Doe";
  config["age"] = 30;
  config["address"] = cait::json::make_object();
  config["address"]["street"] = "123 Main St";
  config["address"]["city"] = "Anytown";
  config["address"]["zip"] = "12345";
  config["phone_numbers"] = cait::json::make_array("555-1234", "555-5678");

  cait::println(config);
  return 0;
}
```

- Native JSON

```c++
#include <caitlyn/core/io.h>
#include <caitlyn/ser/json.h>

int main() {
  const auto config = json_str(
    {
      "name": {
        "first": "John",
        "last": "Doe"
      },
      "age": 30,
      "address": {
        "street": "123 Main St",
        "city": "Anytown",
        "zip": "12345"
      },
      "phone_numbers": [
        "555-1234",
        "555-5678"
      ]
    }
  );
  cait::println(config);
  return 0;
}
```

- Optimized output

```c++
config.to_string();
```

- Structured output

```c++
// Pass true and optional indent width (2 by default)
config.to_string(true);
config.to_string(true, 2);
```

**Output**

```json
{"name":{"first":"John","last":"Doe"},"age":30,"address":{"street":"123 Main St","city":"Anytown","zip":"12345"},"phone_numbers":["555-1234","555-5678"]}
```

```json
{
  "name": {
    "first": "John",
    "last": "Doe"
  },
  "age": 30,
  "address": {
    "street": "123 Main St",
    "city": "Anytown",
    "zip": "12345"
  },
  "phone_numbers": [
    "555-1234",
    "555-5678"
  ]
}
```

### Error Handling

Handling errors without standard exceptions.

- `result_t`: Represents a type to encapsulate the result of an operation that
  may succeed or fail, along with an associated error type.
  It provides a type-safe way to handle both successful outcomes and errors
  without relying on exceptions.

- `error_t`: Represents error types used in conjunction with `result_t`
  for detailed error reporting and handling within operations.
  It provides a structured way to categorize and manage errors that occur during
  computations or operations.

**Usage**

```c++
#include <caitlyn/core/error.h>
#include <caitlyn/core/io.h>

enum class MathError {
  kDivideByZero
};

auto Divide(const double lhs, const double rhs)
    -> cait::result_t<double, MathError> {
  if (lhs == 0 || rhs == 0) {
    return cait::make_error(MathError::kDivideByZero);
  }
  return lhs / rhs;
}

int main() {
  const auto result = Divide(64, 4);
  
  if (result) {
    cait::println("64 / 4 = {}", result.get());
  } else {
    if (result.get_error() == MathError::kDivideByZero) {
      cait::eprintln("Error: divide by zero");
    }
  }
  return 0;
}
```

### Numeric

#### Arbitrary-precision Numbers

Arbitrary-precision types provides tools for working with numbers of any size
or precision, unrestricted by standard data types like `int` or `float`.
It enables performing arithmetic operations, comparisons, and other mathematical
computations with high precision, avoiding data loss due to type limitations.
Such types are often used in applications requiring high-precision calculations,
such as financial applications, scientific research, or cryptography.

- `pwrint_t`: Integral type of arbitrary length
- `pwrnum_t`: Floating point type with arbitrary precision

**Usage**

- Integral

```c++
#include <caitlyn/core/io.h>
#include <caitlyn/num.h>

int main() {
  const auto a = "47011878636176761032731633812398273982371829"_pwrint;
  const auto b = "10218827321893782973821793709217371273"_pwrint;
  const auto result = a * b;

  cait::println(result);
  return 0;
}
```

```text
480406269860917721318957511814148894618259818296995209585410018969574705029068317
```

- Floating point

```c++
#include <caitlyn/core/io.h>
#include <caitlyn/num.h>

int main() {
  const auto a = "182.81278920101871298728193797392737812737"_pwrnum;
  const auto b = "7.8827318902910380293782646543821795732418"_pwrnum;
  const auto result = a * b;

  cait::println(result);
  return 0;
}
```

```text
1441.64203387923303265813084431780163079588042340079866748019604087803446244208066
```

### Type Traits

**required_t** _**< CONDITION**, **OPTIONAL_RETURN_TYPE >**_

The `required_t` type trait provides a more elegant alternative to
`std::enable_if` for enforcing template constraints in C++.

- **CONDITION**: A boolean value that determines whether the template is
  enabled.
- **OPTIONAL_RETURN_TYPE**: The type to return if the condition is met.
  Defaults to `void`

**Usage**

Use SFINAE with a template default type parameter.

Function template `Add` accepts two parameters of type `T` and returns
their sum. It uses `required_t` to enforce that `T` is an integral type,
as a template default type parameter.

```c++
#include <caitlyn/core/traits.h>

template <typename T, typename = cait::required_t<cait::is_integral<T>()>>
T Add(const T lhs, const T rhs) {
  return lhs + rhs;
}
```

Use SFINAE as a return type constraint.

Function template `Add` uses `required_t` directly in the return type.
This enforces that `T` must be an integral type.

```c++
#include <caitlyn/core/traits.h>

template <typename T>
cait::required_t<cait::is_integral<T>(), T>
Add(const T lhs, const T rhs) {
  return lhs + rhs;
}
```

Use SFINAE as a trailing return type constraint.

Function template `Add` uses a trailing return type to apply the `required_t`
constraint. This ensures that `T` is an integral type.

```c++
#include <caitlyn/core/traits.h>

template <typename T>
auto Add(const T lhs, const T rhs)
    -> cait::required_t<cait::is_integral<T>(), T> {
  return lhs + rhs;
}
```

### Unit Testing

**Caitlyn** includes a lightweight testing component for unit testing within
your projects.

- **Test Definition**: Define tests using macros like `TEST` for standalone
  tests and `TEST_F` for fixture-based tests.
- **Dynamic Test Registration**: Tests are dynamically registered using a
  central registry for easy discovery and execution.
- **Assertions**: Includes assertion macros (`ASSERT_TRUE`, `ASSERT_EQ`, etc.)
  for validating expected behaviors.
- **Detailed Reporting**: Reports detailed information on passed and failed
  tests, aiding in debugging.

**Usage**

```c++
#include <caitlyn/test.h>

TEST(MathTests, TestAddition) {
  ASSERT_EQ(2 + 3, 5);
}

TEST(MathTests, TestFailure) {
  ASSERT_EQ_PRINTABLE(2 + 2, 5);
}

template <typename T>
struct MathFixture {
  T a{};
  T b{};

  MathFixture() {}
  ~MathFixture() {}

  void SetValues(const T& x, const T& y) {
    a = x;
    b = y;
  }
};

TEST_F(MathFixture<int>, TestFixtureAddition) {
  SetValues(1, 2);
  ASSERT_EQ(a + b, 3);
}

int main() {
  return cait::test::registry_t::instance().run_all();
}
```

**Output**

```text
[==========] Running 3 tests from 2 test cases.
[----------] Global test environment set-up.

[----------] 1 tests from MathFixture<int>
[ RUN      ] MathFixture<int>.TestFixtureAddition
[       OK ] MathFixture<int>.TestFixtureAddition (0 ms)
[----------] 1 tests from MathFixture<int> (0 ms total)

[----------] 2 tests from MathTests
[ RUN      ] MathTests.TestAddition
[       OK ] MathTests.TestAddition (0 ms)
[ RUN      ] MathTests.TestFailure
[     FAIL ] MathTests.TestFailure (0 ms)
[     INFO ] Assertion failed: 2 + 2 == 5 (4 != 5)
[----------] 2 tests from MathTests (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test cases ran. (4 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] MathTests.TestFailure

1 FAILED TEST
```

### Utilities

- Get keys and values from the `std::map` using `get_map_keys` and
  `get_map_values`

```c++
#include <caitlyn/core/containers.h>
#include <caitlyn/core/io/print.h>
#include <caitlyn/core/string.h>

int main() {
  const auto map = std::map<int, std::string>{
      {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}};

  for (auto& key : cait::get_map_keys(map)) {
    cait::print("{} ", key);
  }
  cait::println();

  for (auto& value : cait::get_map_values(map)) {
    cait::print("{} ", value);
  }
  return 0;
}
```

```text
1 2 3 4 5
One Two Three Four Five
```
