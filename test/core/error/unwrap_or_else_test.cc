#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, UnwrapOrElse) {
  const cait::error::expected_t<int, cait::basic_string_t<char>> result{
      cait::make_failure("Error message")};

  ASSERT_EQ(result.unwrap_or_else(
                [](const cait::basic_string_t<char>&) { return 42; }),
            42);
}
