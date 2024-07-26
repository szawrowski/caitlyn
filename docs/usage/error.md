# Error Handling

Handling errors without standard exceptions.

- `Expected`: Represents a type to encapsulate the result of an operation that
  may succeed or fail, along with an associated error type.
  It provides a type-safe way to handle both successful outcomes and errors
  without relying on exceptions.

- `Unexpected`: Represents error types used in conjunction with `Expected`
  for detailed error reporting and handling within operations.
  It provides a structured way to categorize and manage errors that occur during
  computations or operations.

## Usage

```c++
#include <Caitlyn/Error>
#include <Caitlyn/IO>

using namespace Caitlyn;

enum class MathError
{
    DivideByZero
};

auto Divide(const double lhs, const double rhs) -> Expected<double, MathError>
{
    if (lhs == 0 || rhs == 0)
    {
        return MakeError(MathError::DivideByZero);
    }
    return lhs / rhs;
}

int main()
{
    const auto result = Divide(64, 4);

    if (result)
    {
        WriteLine("64 / 4 = {}", result.Get());
    }
    else if (result.GetError() == MathError::DivideByZero)
    {
        ErrorWriteLine("Error: divide by zero");
    }
    return 0;
}
```
