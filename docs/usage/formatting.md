# Text Formatting

- `StringBuilder`: - String builder type.
- `String::Format`: - Universal string formatter.

## Usage

```c++
#include <Caitlyn/IO>
#include <Caitlyn/String>

int main()
{
    const cait::String first = "Hello";
    const cait::String second = "world";
    
    const auto data = cait::String::Format("{}, {}!", first, second);
    
    // Alignment
    cait::WriteLine("l: '{:<25}'", data);
    cait::WriteLine("c: '{:^25}'", data);
    cait::WriteLine("r: '{:>25}'\n", data);
    // Precision
    cait::WriteLine("floating: {:.4f}", 64.932698);
    cait::WriteLine("decimal:  {:d}\n", 6427123266375693);
    // Filling
    cait::WriteLine("line: {:-<24}", "");
    cait::WriteLine("fill: {:*^24}\n", "TEXT");
    // Other
    cait::WriteLine("escaped: {{text}}\n");
    
    auto content = cait::MakeText("Text: ");
    content.Append("Lorem ipsum dolor sit amet, ");
    content.AppendLine("consectetur adipiscing elit...");
    content.AppendLine(data);
    
    cait::WriteLine(content);
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
