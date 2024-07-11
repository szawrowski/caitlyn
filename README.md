# Caitlyn

## About

**Caitlyn** is a header-only versatile general-purpose C++ library
designed to enhance productivity for everyday tasks across multiple platforms.

## Features

### **Caitlyn** includes
- Unicode String Handling
- Text Formatting
- I/O and File Management
- JSON Serializing
- Error Handling
- Arbitrary Precision Arithmetic
- Utilities

Supported Platforms: **Linux, Windows, macOS**\
Supported Standard: **C++11** and higher

## Installation Guide

### Step 1: Clone the Repository

First, navigate to your project root directory and create a `lib` folder to hold
external libraries. Then, clone the **Caitlyn** repository into this folder.
Open your terminal and run the following commands:

```shell
mkdir lib
cd lib
git clone https://github.com/szawrowski/caitlyn.git
```

### Step 2: Integrate Caitlyn into Your CMake Project

Add the necessary configurations to your `CMakeLists.txt` file
to include **Caitlyn** in your project.
Use the following template as a reference:

```cmake
cmake_minimum_required(VERSION 3.10)
project(ProjectName)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the path to Caitlyn library
set(CAITLYN_ROOT "${CMAKE_SOURCE_DIR}/lib/caitlyn")
set(CAITLYN_INCLUDE_DIR "${CAITLYN_ROOT}/include")

# Add your main executable
add_executable(${PROJECT_NAME} main.cpp)

# Include Caitlyn directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CAITLYN_INCLUDE_DIR})
```

Replace `ProjectName` with the actual name of your project and ensure `main.cpp`
is the source file for your main executable.

## Examples

### Unicode Strings Support

You can continue using standard C++ strings, supplemented with Unicode wrappers.

**Types:**

- `unichar_t`: Wrapper for Unicode code point characters.
- `unistring_t`: String wrapper based on Unicode code points with iterator support.
- `text_t`: Universal formatting string builder.

**Usage:**

```c++
#include <caitlyn/caitlyn.h>

int main() {
  const auto string = "Hello, 世界!"_str;
  const auto emoji = "🙂"_char;

  const auto formatted = cait::fmt("{} {}", string, emoji);
  cait::println(formatted);

  auto content = cait::make_text();
  content.append("Lorem ipsum dolor sit amet, ");
  content.append_line("consectetur adipiscing elit...");
  content.append_line(formatted);

  auto file = "somefile.txt"_ofile;
  file.write("Text: {}", content);
  file.close();

  return 0;
}

```
**Output:**

- Terminal

```text
Hello, 世界! 🙂
```

- File (_somefile.txt_)

```text
Text: Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, 世界! 🙂
```

### Serializing

#### JSON

The JSON format is crucial for web development, API integration, and any
applications that need efficient data exchange in a structured format.

**Types:**

- `json_t`: Provides comprehensive support for JSON handling.
  Facilitates parsing, generating, and manipulating JSON data structures.
  Enables easy serialization of complex data into JSON format for storage or
  transmission, and deserialization of JSON back into native data structures.
  Offers efficient methods for encoding and decoding JSON, handling nested objects
  and arrays, ensuring compatibility across various platforms and systems.

**Usage:**

- Brackets operator

```c++
#include <caitlyn/caitlyn.h>

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
#include <caitlyn/caitlyn.h>

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

**Output:**

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

**Types:**

- `result_t`: Represents a type to encapsulate the result of an operation that
  may succeed or fail, along with an associated error type.
  It provides a type-safe way to handle both successful outcomes and errors
  without relying on exceptions.

- `error_t`: Represents error types used in conjunction with `result_t`
  for detailed error reporting and handling within operations.
  It provides a structured way to categorize and manage errors that occur during
  computations or operations.

**Usage:**

```c++
#include <caitlyn/caitlyn.h>

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

**Types:**

- `pwrint_t`: Integral type of arbitrary length
- `pwrnum_t`: Floating point type with arbitrary precision

**Usage:**

- Integral

```c++
#include <caitlyn/caitlyn.h>

int main() {
  const auto a = "47011878636176761032731633812398273982371829"_pwrint;
  const auto b = "10218827321893782973821793709217371273"_pwrint;
  const auto result = a * b;

  cait::println(result);
  return 0;
}
```

- Floating point

```c++
#include <caitlyn/caitlyn.h>

int main() {
  const auto a = "182.81278920101871298728193797392737812737"_pwrnum;
  const auto b = "7.8827318902910380293782646543821795732418"_pwrnum;
  const auto result = a * b;

  cait::println(result);
  return 0;
}
```

**Output:**

```text
480406269860917721318957511814148894618259818296995209585410018969574705029068317
1441.64203387923303265813084431780163079588042340079866748019604087803446244208066
```
