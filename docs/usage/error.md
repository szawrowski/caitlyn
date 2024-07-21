### Error Handling

Handling errors without standard exceptions.

- `expected`: Represents a type to encapsulate the result of an operation that
  may succeed or fail, along with an associated error type.
  It provides a type-safe way to handle both successful outcomes and errors
  without relying on exceptions.

- `unexpected`: Represents error types used in conjunction with `expected`
  for detailed error reporting and handling within operations.
  It provides a structured way to categorize and manage errors that occur during
  computations or operations.

**Usage**

```c++
#include <caitlyn/error>
#include <caitlyn/io>

enum class MathError {
  kDivideByZero
};

auto Divide(const double lhs, const double rhs)
    -> cait::expected<double, MathError> {
  if (lhs == 0 || rhs == 0) {
    return cait::make_failure(MathError::kDivideByZero);
  }
  return lhs / rhs;
}

int main() {
  const auto result = Divide(64, 4);
  
  if (result) {
    cait::println("64 / 4 = {}", result.get());
  } else {
    if (result.get_error() == MathError::kDivideByZero) {
      cait::eprintln("Error: divide by zero");
    }
  }
  return 0;
}
```
