# Caitlyn
A general-purpose library designed to enhance productivity for everyday tasks.\
Supported standard: C++17

## Features

### Unicode Strings Support
Easily handle Unicode strings, characters and files.\
Supported platforms: **Linux, Windows, macOS**.

#### Usage
```c++
#include <caitlyn/caitlyn.h>

int main() {
  const auto str = "Hello, 世界!"_str;
  const auto emoji = "🙂"_char;
  
  auto text = cait::fmt("{} {}", str, emoji);
  cait::println("{}", text);

  auto file = "somefile.txt"_ofile;
  file.write_line("Text: {} {}", str, emoji);
  file.close();

  return 0;
}
```
#### Output
- Terminal
```text
Hello, 世界! 🙂
```
- File (_somefile.txt_)
```text
Text: Hello, 世界! 🙂
```
##

### JSON Support
Seamlessly serialize and deserialize data in JSON format.

#### Usage
- Using brackets operator
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
  
  std::cout << config << std::endl;
  return 0;
}
```

- Using methods
```c++
#include <caitlyn/caitlyn.h>

int main() {
  auto config = cait::make_json();
  config.add_member("name", cait::json::make_object());
  config.add_member(json_path("name", "first"), "John");
  config.add_member(json_path("name", "second"), "Doe");
  config.add_member("age", 30);
  config.add_member("address", cait::json::make_object());
  config.add_member(json_path("address", "street"), "123 Main St");
  config.add_member(json_path("address", "city"), "Anytown");
  config.add_member(json_path("address", "zip"), "12345");
  config.add_member("phone_numbers", cait::json::make_array("555-1234", "555-5678"));
  
  std::cout << config << std::endl;
  return 0;
}
```
- Using native JSON
```c++
#include <caitlyn/caitlyn.h>

int main() {
  const auto config = json_str(
    {
      "name": {
        "first": "John",
        "last": "Doe"
      },
      "age": 30
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
  std::cout << config << std::endl;
  return 0;
}
```
#### Output
- Optimized
```c++
config.to_string();
```
```json
{"name":{"first":"John","last":"Doe"},"age":30,"address":{"street":"123 Main St","city":"Anytown","zip":"12345"},"phone_numbers":["555-1234","555-5678"]}
```
- Beauty

Pass **true** for mangling and optional indent width (2 by default)
```c++
config.to_string(true);  // or
config.to_string(true, 2);
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
##

### Error Handling
Easily handle errors without exceptions.

#### Usage
- Using brackets operator
```c++
#include <caitlyn/caitlyn.h>

enum class MathError {
  kDivideByZero
};

auto Divide(const double lhs, const double rhs)
    -> cait::result_t<double, MathError> {
  if (lhs == 0 || rhs == 0) {
    return cait::make_error{MathError::kDivideByZero};
  }
  return lhs / rhs;
}

int main() {
  auto result = Divide(64, 4);
  
  if (result.has_value()) {
    std::cout << "64 / 4 = " << result.get() << std::endl;
  } else if (result.get_error() == MathError::kDivideByZero) {
    std::cerr << "Error: divide by zero" << std::endl;
  }
  return 0;
}
```
##

### Arbitrarily Large Numbers

#### Usage
- Integral
```c++
#include <caitlyn/caitlyn.h>

int main() {
  const cait::pwrint_t lhs = "47011878636176761032731633812398273982371829";
  const cait::pwrint_t rhs = "10218827321893782973821793709217371273";

  std::cout << lhs * rhs << std::endl;
  return 0;
}
```
- Floating point
```c++
#include <caitlyn/caitlyn.h>

int main() {
  const cait::pwrnum_t lhs = "182.81278920101871298728193797392737812737";
  const cait::pwrnum_t rhs = "7.8827318902910380293782646543821795732418";

  std::cout << lhs * rhs << std::endl;
  return 0;
}
```
#### Output
```text
480406269860917721318957511814148894618259818296995209585410018969574705029068317
1441.64203387923303265813084431780163079588042340079866748019604087803446244208066
```
