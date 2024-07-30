# Unicode String Support

Basic string enhanced with correct UTF-8 operations.

## Usage

```c++
#include <Caitlyn/IO>
#include <Caitlyn/String>

using namespace Caitlyn;

int main()
{
    String string = "Hello, 世界!";
    Char emoji = "🙂";

    auto data = String::Format("{} {}", string, emoji);

    OutputStream::WriteLine("string: {}", data);
    OutputStream::WriteLine("substring from index 7, length 2: {}", data.Substring(7, 2));
    OutputStream::WriteLine("starts with 'Hello'? {}", data.StartsWith("Hello"));
    OutputStream::WriteLine("ends with 🙂? {}", data.EndsWith("🙂"));
    OutputStream::WriteLine("contains '世界'? {}", data.Contains("世界"));
    OutputStream::WriteLine("index of '世': {}", data.Find("世"));
    OutputStream::WriteLine("index of '🙂': {}", data.Find("🙂"));
    OutputStream::WriteLine("last index of ' ': {}", data.ReverseFind(" "));
    OutputStream::WriteLine("char count: {}", data.Length());
    OutputStream::WriteLine("byte count: {}", data.ByteCount());
    OutputStream::WriteLine("char at index 1: {}", data.At(1));
    OutputStream::WriteLine("char at index 9: {}", data.At(9));

    for (auto& elem : data)
    {
        if (elem == "🙂")
        {
            elem = "🍉";
        }
    }
    OutputStream::WriteLine("updated: {}\n", data);
    return 0;
}
```

### Output

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
char at index 1: e
char at index 9: !
updated: Hello, 世界! 🍉
```
