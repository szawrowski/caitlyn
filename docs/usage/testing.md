# Unit Testing

**Caitlyn** includes a lightweight testing component for unit testing within
your projects.

- **Test Definition**: Define tests using macros like `TEST` for standalone
  tests and `TEST_F` for fixture-based tests.
- **Dynamic Test Registration**: Tests are dynamically registered using a
  central registry for easy discovery and execution.
- **Assertions**: Includes assertion macros (`ASSERT_TRUE`, `ASSERT_EQ`, etc.)
  for validating expected behaviors.
- **Detailed Reporting**: Reports detailed information on passed and failed
  tests, aiding in debugging.

## Usage

```c++
#include <caitlyn/testing>

TEST(MathTests, TestAddition)
{
    ASSERT_EQ(2 + 3, 5);
}

TEST(MathTests, TestFailure)
{
    ASSERT_EQ_PRINTABLE(2 + 2, 5);
}

template <typename T>
struct MathFixture
{
    T a{};
    T b{};

    MathFixture()
    {
    }
    
    ~MathFixture()
    {
    }

    void SetValues(const T& x, const T& y)
    {
        a = x;
        b = y;
    }
};

TEST_F(MathFixture<int>, TestFixtureAddition)
{
    SetValues(1, 2);
    ASSERT_EQ(a + b, 3);
}

int main()
{
    return cait::test::registry::instance().run_all();
}
```

### Output

```text
[==========] Running 3 tests from 2 test cases.
[----------] Global test environment set-up.

[----------] 1 tests from MathFixture<int>
[ RUN      ] MathFixture<int>.TestFixtureAddition
[       OK ] MathFixture<int>.TestFixtureAddition (0 ms)
[----------] 1 tests from MathFixture<int> (0 ms total)

[----------] 2 tests from MathTests
[ RUN      ] MathTests.TestAddition
[       OK ] MathTests.TestAddition (0 ms)
[ RUN      ] MathTests.TestFailure
[     FAIL ] MathTests.TestFailure (0 ms)
[     INFO ] Assertion failed: 2 + 2 == 5 (4 != 5)
[----------] 2 tests from MathTests (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test cases ran. (4 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] MathTests.TestFailure

1 FAILED TEST
```
