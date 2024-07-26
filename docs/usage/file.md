# File Management

- `File`: Universal file handler.

## Usage

- Write text to file

```c++
#include <Caitlyn/File>

int main()
{
    const cait::String some = "Lorem ipsum dolor sit amet,";
    const cait::String other = "consectetur adipiscing elit...";
    const cait::String unicode = "Hello, 世界!";

    auto file = cait::MakeFile("somefile.txt");
    file.Write("{} {}\n{}", some, other, unicode);
    file.Close();
  
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
#include <Caitlyn/IO>

int main()
{
    auto file = cait::MakeFile("somefile.txt");
    
    while (file)
    {
        cait::WriteLine("{}", file.ReadLine());
    }
    file.Close();
    return 0;
}
```

```text
Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, 世界!
```
