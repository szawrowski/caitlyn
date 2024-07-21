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
  cait::println("find(!)... found at: {}", data.find("!"));
  
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
find(!)... found at: 9
updated: Hello, 世界! 🍉
```
