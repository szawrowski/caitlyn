### Numeric

#### Arbitrary-precision Numbers

Arbitrary-precision types provides tools for working with numbers of any size
or precision, unrestricted by standard data types like `int` or `float`.
It enables performing arithmetic operations, comparisons, and other mathematical
computations with high precision, avoiding data loss due to type limitations.
Such types are often used in applications requiring high-precision calculations,
such as financial applications, scientific research, or cryptography.

- `pwrint`: Integral type of arbitrary length
- `pwrnum`: Floating point type with arbitrary precision

**Usage**

- Integral

```c++
#include <caitlyn/io>
#include <caitlyn/numeric>

int main() {
  const pwrint a = "47011878636176761032731633812398273982371829";
  const pwrint b = "10218827321893782973821793709217371273";
  const auto result = a * b;

  cait::println(result);
  return 0;
}
```

```text
480406269860917721318957511814148894618259818296995209585410018969574705029068317
```

- Floating point

```c++
#include <caitlyn/io>
#include <caitlyn/numeric>

int main() {
  const pwrnum a = "182.81278920101871298728193797392737812737";
  const pwrnum b = "7.8827318902910380293782646543821795732418";
  const auto result = a * b;

  cait::println(result);
  return 0;
}
```

```text
1441.64203387923303265813084431780163079588042340079866748019604087803446244208066
```