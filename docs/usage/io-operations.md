# IO Operations

Easily read and write text from the console with formatting support.

## Usage

```c++
#include <Caitlyn/IO>

using namespace Caitlyn;

int main()
{
    Write("Some");
    WriteLine("Other");
    WriteLine("On new line");
    
    const auto str = ReadLine("Input string: "); // standard input
    WriteLine("stdin: {}", str); // standard output
    
    const auto c = ReadChar("Input char: ");
    WriterLine("stdin: {}", c);
    
    ErrorWriteLine("Some error"); // standard error (unbuffered)
    Log("Message"); // standard error (buffered)
    
    auto content = MakeText("Text: ");
    content.Append("Lorem ipsum dolor sit amet, ");
    content.AppendLine("consectetur adipiscing elit...");
    content.AppendLine("Hello, world!");
    
    WriteLine(content);
    
    return 0;
}
```

### Output

```text
SomeOther
On new line
Input string: example
stdin: example
Input char: 🙂
stdin: 🙂
Some error
Message
Text: Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, world!
```
