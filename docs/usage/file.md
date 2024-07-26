# File Management

- `File`: Universal file handler.

## Usage

- Write text to file

```c++
#include <Caitlyn/File>

using namespace Caitlyn;

int main()
{
    const String some = "Lorem ipsum dolor sit amet,";
    const String other = "consectetur adipiscing elit...";
    const String unicode = "Hello, 世界!";

    auto file = MakeFile("somefile.txt");
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

using namespace Caitlyn;

int main()
{
    auto file = MakeFile("somefile.txt");
    
    while (file)
    {
        WriteLine("{}", file.ReadLine());
    }
    file.Close();
    return 0;
}
```

```text
Lorem ipsum dolor sit amet, consectetur adipiscing elit...
Hello, 世界!
```
