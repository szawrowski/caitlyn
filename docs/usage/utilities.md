# Utilities

#### Get keys and values from a map

```c++
#include <Caitlyn/Collections>
#include <Caitlyn/IO>
#include <Caitlyn/String>

using namespace Caitlyn;

int main()
{
    const std::map<int, String> numbers{{1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}};

    for (auto& key : GetMapKeys(numbers))
    {
        Write("{} ", key);
    }
    WriteLine();

    for (auto& value : GetMapValues(numbers))
    {
        Write("{} ", value);
    }
    return 0;
}
```

```text
1 2 3 4 5
One Two Three Four Five
```
