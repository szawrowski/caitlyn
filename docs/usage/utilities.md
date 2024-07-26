# Utilities

#### Get keys and values from a map

```c++
#include <Caitlyn/Collections>
#include <Caitlyn/IO>
#include <Caitlyn/String>

int main()
{
    const std::map<int, cait::String> numbers{{1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}};

    for (auto& key : cait::GetMapKeys(numbers))
    {
        cait::Write("{} ", key);
    }
    cait::WriteLine();

    for (auto& value : cait::GetMapValues(numbers))
    {
        cait::Write("{} ", value);
    }
    return 0;
}
```

```text
1 2 3 4 5
One Two Three Four Five
```
