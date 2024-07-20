# Caitlyn

## About

**Caitlyn** is a header-only versatile general-purpose C++ library designed to
enhance productivity for everyday tasks.

## Features

### Caitlyn includes
- [Unicode String Support](https://github.com/szawrowski/caitlyn?tab=readme-ov-file#unicode-string-support)
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

## Examples

### Unicode String Support

Basic string enhanced with correct UTF-8 operations.

**Usage**

```c++
#include <caitlyn/io>
#include <caitlyn/string>

int main() {
  cait::string data = "Hello, 世界! 🙂";

  cait::println("string: {}", data);
  cait::println("substring (from 7): {}", data.substr(7));

  cait::println("char count: {}", data.size());
  cait::println("byte count: {}", data.byte_count());

  cait::println("starts with H? {}", data.starts_with("H"));
  cait::println("ends with 🙂? {}", data.ends_with("🙂"));
  cait::println("contains '世界'? {}", data.contains("世界"));
  cait::println("contains 'some text'? {}", data.contains("some text"));

  cait::println("char at position 0: {}", data[0]);
  cait::println("char at position 7: {}", data.at(7));
  
  for (auto&& elem : data) {
    if (elem == "🙂") {
      elem = "🍉";
    }
  }
  cait::println("updated: {}", data);
  return 0;
}
```

**Output:**

```text
string: Hello, 世界! 🙂
substring (from 7): 世界! 🙂
char count: 12
byte count: 19
starts with H? true
ends with 🙂? true
contains '世界'? true
contains 'some text'? false
char at position 0: H
char at position 7: 世
updated: Hello, 世界! 🍉
```

### Text Formatting

- `text_builder`: - String builder type.
- `format`: - Universal string formatter.

**Usage**

```c++
#include <caitlyn/io>
#include <caitlyn/text>

int main() {
  const cait::string first = "Hello";
  const cait::string second = "world";

  const auto data = cait::format("{}, {}!", first, second);

  // Alignment
  cait::println("l: '{:<25}'", data);
  cait::println("c: '{:^25}'", data);
  cait::println("r: '{:>25}'\n", data);
  // Precision
  cait::println("floating: {:.4f}", 64.932698);
  cait::println("decimal:  {:d}\n", 6427123266375693);
  // Filling
  cait::println("line: {:-<24}", "");
  cait::println("fill: {:*^24}\n", "TEXT");
  // Other
  cait::println("escaped: {{text}}\n");

  auto content = cait::make_text("Text: ");
  content.append("Lorem ipsum dolor sit amet, ");
  content.appendln("consectetur adipiscing elit...");
  content.appendln(data);

  cait::println(content);
  return 0;
}
```

**Output:**

```text
l: 'Hello, world!            '
c: '      Hello, world!      '
r: '            Hello, world!'

floating: 64.9326
decimal:  6427123266375693

line: ------------------------
fill: **********TEXT**********

escaped: {text}

Text: Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, world!
```

### File Management

- `file`: Universal file handler.

**Usage**

- Write text to file

```c++
#include <caitlyn/file>

int main() {
  const auto some = "Lorem ipsum dolor sit amet,"_str;
  const auto other = "consectetur adipiscing elit..."_str;
  const auto unicode = "Hello, 世界!"_str;

  auto file = cait::make_file("somefile.txt");
  file.writef("{} {}\n{}", some, other, unicode);
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
#include <caitlyn/io>

int main() {
  auto file = cait::make_file("somefile.txt");
  
  while (file) {
    cait::println("{}", file.readln());
  }
  file.close();
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

- `document`: Provides comprehensive support for JSON handling.
  Facilitates parsing, generating, and manipulating JSON data structures.
  Enables easy serialization of complex data into JSON format for storage or
  transmission, and deserialization of JSON back into native data structures.
  Offers efficient methods for encoding and decoding JSON, handling nested
  objects and arrays, ensuring compatibility across various platforms and
  systems.

**Usage**

- Brackets operator

```c++
#include <caitlyn/io>
#include <caitlyn/serializing>

int main() {
  auto config = cait::json::make_document();
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
#include <caitlyn/io>
#include <caitlyn/serializing>

int main() {
  const auto config = JSON_STRING(
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
config.str();
```

- Structured output

```c++
// Pass true and optional indent width (2 by default)
config.str(true);
config.str(true, 2);
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

- `expected`: Represents a type to encapsulate the result of an operation that
  may succeed or fail, along with an associated error type.
  It provides a type-safe way to handle both successful outcomes and errors
  without relying on exceptions.

- `unexpected`: Represents error types used in conjunction with `expected`
  for detailed error reporting and handling within operations.
  It provides a structured way to categorize and manage errors that occur during
  computations or operations.

**Usage**

```c++
#include <caitlyn/error>
#include <caitlyn/io>

enum class MathError {
  kDivideByZero
};

auto Divide(const double lhs, const double rhs)
    -> cait::expected<double, MathError> {
  if (lhs == 0 || rhs == 0) {
    return cait::make_failure(MathError::kDivideByZero);
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

- `pwrint`: Integral type of arbitrary length
- `pwrnum`: Floating point type with arbitrary precision

**Usage**

- Integral

```c++
#include <caitlyn/io>
#include <caitlyn/numeric>

int main() {
  const pwrint a = "47011878636176761032731633812398273982371829";
  const pwrint b = "10218827321893782973821793709217371273";
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
#include <caitlyn/io>
#include <caitlyn/numeric>

int main() {
  const pwrnum a = "182.81278920101871298728193797392737812737";
  const pwrnum b = "7.8827318902910380293782646543821795732418";
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

The `required` type trait provides a more elegant alternative to
`std::enable_if` for enforcing template constraints in C++.

- **CONDITION**: A boolean value that determines whether the template is
  enabled.
- **OPTIONAL_RETURN_TYPE**: The type to return if the condition is met.
  Defaults to `void`

**Usage**

Use SFINAE with a template default type parameter.

Function template `Add` accepts two parameters of type `T` and returns
their sum. It uses `required` to enforce that `T` is an integral type,
as a template default type parameter.

```c++
#include <caitlyn/traits>

template <typename T, typename = cait::required<cait::is_integral<T>()>>
T Add(const T lhs, const T rhs) {
  return lhs + rhs;
}
```

Use SFINAE as a return type constraint.

Function template `Add` uses `required` directly in the return type.
This enforces that `T` must be an integral type.

```c++
#include <caitlyn/traits>

template <typename T>
cait::required<cait::is_integral<T>(), T>
Add(const T lhs, const T rhs) {
  return lhs + rhs;
}
```

Use SFINAE as a trailing return type constraint.

Function template `Add` uses a trailing return type to apply the `required`
constraint. This ensures that `T` is an integral type.

```c++
#include <caitlyn/traits>

template <typename T>
auto Add(const T lhs, const T rhs)
    -> cait::required<cait::is_integral<T>(), T> {
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
#include <caitlyn/testing>

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
  return cait::test::registry::instance().run_all();
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
#include <caitlyn/containers>
#include <caitlyn/io>
#include <caitlyn/string>

int main() {
  const std::map<int, std::string> numbers{
      {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}};

  for (auto& key : cait::get_map_keys(numbers)) {
    cait::print("{} ", key);
  }
  cait::println();

  for (auto& value : cait::get_map_values(numbers)) {
    cait::print("{} ", value);
  }
  return 0;
}
```

```text
1 2 3 4 5
One Two Three Four Five
```
