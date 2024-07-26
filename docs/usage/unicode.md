# Unicode String Support

Basic string enhanced with correct UTF-8 operations.

## Usage

```c++
#include <Caitlyn/IO>
#include <Caitlyn/String>

int main()
{
    cait::String string = "Hello, 世界!";
    cait::Char emoji = "🙂";

    auto data = cait::String::Format("{} {}", string, emoji);

    cait::WriteLine("string: {}", data);
    cait::WriteLine("substring from index 7, length 2: {}", data.Substring(7, 2));
    cait::WriteLine("starts with 'Hello'? {}", data.StartsWith("Hello"));
    cait::WriteLine("ends with 🙂? {}", data.EndsWith("🙂"));
    cait::WriteLine("contains '世界'? {}", data.Contains("世界"));
    cait::WriteLine("index of '世': {}", data.Find("世"));
    cait::WriteLine("index of '🙂': {}", data.Find("🙂"));
    cait::WriteLine("last index of ' ': {}", data.ReverseFind(" "));
    cait::WriteLine("char count: {}", data.Length());
    cait::WriteLine("byte count: {}", data.ByteCount());
    cait::WriteLine("char at index 1: {}", data.At(1));
    cait::WriteLine("char at index 9: {}", data.At(9));

    for (auto& elem : data)
    {
        if (elem == "🙂")
        {
            elem = "🍉";
        }
    }
    cait::WriteLine("updated: {}\n", data);
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
