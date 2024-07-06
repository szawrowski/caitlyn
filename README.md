# Caitlyn

### General-purpose library for solving everyday tasks more productively

- ### Unicode strings support
#### Usage
```c++
#include <iostream>
#include <caitlyn/core.h>

int main() {
  const auto str = "Hello, 世界!"_str;
  const auto emoji = "🙂"_char;
  std::cout << str << ' ' << emoji << std::endl;
  return 0;
}
```

#### Output
```
Hello, 世界! 🙂
```
