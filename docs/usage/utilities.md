# Utilities

#### Get keys and values from a map

```c++
#include <caitlyn/containers>
#include <caitlyn/io>
#include <caitlyn/string>

int main()
{
    const std::map<int, cait::string> numbers{{1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}};

    for (auto& key : cait::get_map_keys(numbers))
    {
        cait::print("{} ", key);
    }
    cait::println();

    for (auto& value : cait::get_map_values(numbers))
    {
        cait::print("{} ", value);
    }
    return 0;
}
```

```text
1 2 3 4 5
One Two Three Four Five
```
