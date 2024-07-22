# File Management

- `file`: Universal file handler.

## Usage

- Write text to file

```c++
#include <caitlyn/file>

int main() {
  const cait::string some = "Lorem ipsum dolor sit amet,";
  const cait::string other = "consectetur adipiscing elit...";
  const cait::string unicode = "Hello, 世界!";

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
