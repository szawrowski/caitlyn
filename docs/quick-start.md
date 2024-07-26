# Quick Start

#### Run the simple program

```c++
#include <Caitlyn/IO>

int main()
{
    Caitlyn::WriteLine("Hello, world!");
    return 0;
}
```

#### Make your program work correctly on all platforms

```c++
int main()
{
    const auto app = Caitlyn::Application::Initialize();
    // ...
}
```

#### Handling arguments and additional operations

```c++
int main(int argc, const char** argv)
{
    const auto app = Caitlyn::Application::Initialize(argc, argv);

    // Get vector of arguments
    for (const auto& arg : app->GetArgs())
    {
        Caitlyn::WriteLine("{} ", arg);
    }
    // Get information
    Caitlyn::WriteLine(app->GetSystemName());
    Caitlyn::WriteLine(app->GetCompilerInfo());
    Caitlyn::WriteLine(app->GetCaitlynInfo());
    // ...
}
```
