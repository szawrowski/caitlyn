#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, AndThen) {
  const cait::error::expected_t<int, cait::basic_string_t<char>> result{42};

  const auto next_result = result.and_then([](const int value) {
    return cait::make_correct<int, cait::basic_string_t<char>>(value * 2);
  });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 84);
}