# Text Formatting

- `StringBuilder`: - String builder type.
- `String::Format`: - Universal string formatter.

## Usage

```c++
#include <Caitlyn/IO>

using namespace Caitlyn;

int main()
{
    const String first = "Hello";
    const String second = "world";
    
    const auto data = String::Format("{}, {}!", first, second);
    
    // Alignment
    WriteLine("l: '{:<25}'", data);
    WriteLine("c: '{:^25}'", data);
    WriteLine("r: '{:>25}'\n", data);
    // Precision
    WriteLine("floating: {:.4f}", 64.932698);
    WriteLine("decimal:  {:d}\n", 6427123266375693);
    // Filling
    WriteLine("line: {:-<24}", "");
    WriteLine("fill: {:*^24}\n", "TEXT");
    // Other
    WriteLine("escaped: {{text}}\n");
    
    return 0;
}
```

### Output

```text
l: 'Hello, world!            '
c: '      Hello, world!      '
r: '            Hello, world!'

floating: 64.9326
decimal:  6427123266375693

line: ------------------------
fill: **********TEXT**********

escaped: {text}
```
