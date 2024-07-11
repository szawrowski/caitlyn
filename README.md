# Caitlyn

## About

Caitlyn is a versatile general-purpose C++ library designed to enhance
productivity for everyday tasks across multiple platforms.

It includes:
- Unicode String Handling
- Text Formatting
- JSON Serialization
- I/O and File Management
- Error Handling
- Arbitrary precision arithmetic
- Utility Functions

Supported platforms: **Linux, Windows, macOS**.\
Supported standard: **C++11** and higher.

## Features

### Unicode Strings Support

Robust support for Unicode strings, characters, and files.

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

  const auto formatted = cait::format("{} {}", string, emoji);
  cait::println(formatted);

  auto content = cait::make_text();
  content.append("Lorem ipsum dolor sit amet, ");
  content.append_line("consectetur adipiscing elit.");
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
Text: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Hello, 世界! 🙂
```

### Serializing

#### JSON

**Types:**

- `json_t`: provides comprehensive support for JSON handling.

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

  cait::println(config.to_string());
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
  cait::println(config.to_string());
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

The `result_t` class is designed to encapsulate the result of an operation that
may succeed or fail, along with an associated error type.
It provides a type-safe way to handle both successful outcomes and errors
without relying on exceptions.

The `error_t` class represents error types used in conjunction with `result_t`
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

#### Arbitrarily Large Numbers

- `pwrint_t`: integral type with basic arithmetic support.
- `pwrnum_t`: floating point type with basic arithmetic support.

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
