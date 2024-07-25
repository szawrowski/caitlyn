# Quick Start

#### Run the simple program

```c++
#include <caitlyn/io>

int main()
{
    cait::println("Hello, world!");
    return 0;
}
```

#### Make your program work correctly on all platforms

```c++
int main()
{
    const auto app = cait::application::init();    
    // ...
}
```

#### Handling arguments and additional operations

```c++
int main(int argc, const char** argv)
{
    const auto app = cait::application::init(argc, argv);
  
    // Get vector of arguments
    for (const auto& arg : app->get_args())
    {
        cait::println("{} ", arg);
    }
    // Get information
    cait::println(app->get_system());
    cait::println(app->get_compiler());
    cait::println(app->get_caitlyn_info());
    // ...
}
```
