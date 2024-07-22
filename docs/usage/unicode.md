### Unicode String Support

Basic string enhanced with correct UTF-8 operations.

**Usage**

```c++
#include <caitlyn/io>
#include <caitlyn/string>

int main() {
  cait::string str = "Hello, 世界!";
  cait::character emoji = "🙂";

  auto data = cait::format("{} {}", str, emoji);

  cait::println("string: {}", data);
  cait::println("substring from index 7, length 2: {}", data.substr(7, 2));
  cait::println("starts with 'Hello'? {}", data.starts_with("Hello"));
  cait::println("ends with 🙂? {}", data.ends_with("🙂"));
  cait::println("contains '世界'? {}", data.contains("世界"));
  cait::println("index of '世': {}", data.find("世"));
  cait::println("index of '🙂': {}", data.find("🙂"));
  cait::println("last index of ' ': {}", data.rfind(" "));
  cait::println("char count: {}", data.size());
  cait::println("byte count: {}", data.byte_count());
  cait::println("char at index 0: {}", data[0]);
  cait::println("char at index 9: {}", data[9]);

  for (auto& elem : data) {
    if (elem == "🙂") {
      elem = "🍉";
    }
  }
  cait::println("updated: {}\n", data);
  return 0;
}
```

**Output:**

```text
string: Hello, 世界! 🙂
substring from index 7, length 2: 世界
starts with 'Hello'? true
ends with 🙂? true
contains '世界'? true
index of '世': 7
index of '🙂': 11
last index of ' ': 10
char count: 12
byte count: 19
char at index 0: H
char at index 9: !
updated: Hello, 世界! 🍉
```
