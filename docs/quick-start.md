# Quick Start

#### Run the simple program

```c++
#include <Caitlyn/IO>

int main()
{
    cait::WriteLine("Hello, world!");
    return 0;
}
```

#### Make your program work correctly on all platforms

```c++
int main()
{
    const auto app = cait::Application::Initialize();
    // ...
}
```

#### Handling arguments and additional operations

```c++
int main(int argc, const char** argv)
{
    const auto app = cait::Application::Initialize(argc, argv);

    // Get vector of arguments
    for (const auto& arg : app->GetArgs())
    {
        cait::WriteLine("{} ", arg);
    }
    // Get information
    cait::WriteLine(app->GetSystemName());
    cait::WriteLine(app->GetCompilerInfo());
    cait::WriteLine(app->GetCaitlynInfo());
    // ...
}
```
