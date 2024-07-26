# Type Traits

The `Required` type trait provides a more elegant alternative to
`std::enable_if` for enforcing template constraints in C++.

**required** _**< CONDITION**, **OPTIONAL_RETURN_TYPE >**_

- **CONDITION**: A boolean value that determines whether the template is
  enabled.
- **OPTIONAL_RETURN_TYPE**: The type to return if the condition is met.
  Defaults to `void`

## Usage

#### SFINAE with a template default type parameter

Function template `Add` accepts two parameters of type `T` and returns
their sum. It uses `Required` to enforce that `T` is an integral type,
as a template default type parameter.

```c++
#include <Caitlyn/Traits>

using namespace Caitlyn;

template <typename T, typename = Required<IsIntegral<T>()>>
T Add(const T lhs, const T rhs)
{
    return lhs + rhs;
}
```

#### SFINAE as a return type constraint

Function template `Add` uses `Required` directly in the return type.
This enforces that `T` must be an integral type.

```c++
#include <Caitlyn/Traits>

using namespace Caitlyn;

template <typename T>
Required<IsIntegral<T>(), T> Add(const T lhs, const T rhs)
{
    return lhs + rhs;
}
```

#### SFINAE as a trailing return type constraint

Function template `Add` uses a trailing return type to apply the `Required`
constraint. This ensures that `T` is an integral type.

```c++
#include <Caitlyn/Traits>

using namespace Caitlyn;

template <typename T>
auto Add(const T lhs, const T rhs) -> Required<IsIntegral<T>(), T>
{
    return lhs + rhs;
}
```
