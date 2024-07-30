# IO Operations

Easily read and write text from the console with formatting support.

## Usage

```c++
#include <Caitlyn/IO>

using namespace Caitlyn;

int main()
{
    OutputStream::Write("Some");
    OutputStream::WriteLine("Other");
    OutputStream::WriteLine("On new line");
    
    const auto str = InputStream::ReadLine("Input string: "); // standard input
    OutputStream::WriteLine("stdin: {}", str); // standard output
    
    const auto c = InputStream::ReadChar("Input char: ");
    OutputStream::WriterLine("stdin: {}", c);
    
    ErrorStream::WriteLine("Some error"); // standard error (unbuffered)
    LogStream::WriteLine("Message"); // standard error (buffered)
    
    auto content = MakeText("Text: ");
    content.Append("Lorem ipsum dolor sit amet, ");
    content.AppendLine("consectetur adipiscing elit...");
    content.AppendLine("Hello, world!");
    
    OutputStream::WriteLine(content);
    
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
