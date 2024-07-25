# Text Formatting

- `text_builder`: - String builder type.
- `format`: - Universal string formatter.

## Usage

```c++
#include <caitlyn/io>
#include <caitlyn/text>

int main()
{
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

Text: Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, world!
```
