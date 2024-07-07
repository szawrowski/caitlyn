#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, FoldValue) {
  const cait::result_t<int, cait::string_t> result{42};

  const auto folded = result.fold(
      10, [](const int acc, const int value) { return acc + value; });

  ASSERT_EQ(folded, 52);
}

TEST(ResultTest, FoldError) {
  const cait::result_t<int, cait::string_t> result{
      cait::error_t<cait::string_t>{"Error message"}};

  const auto folded = result.fold(
      10, [](const int acc, const int value) { return acc + value; });

  ASSERT_EQ(folded, 10);  // Initial value should remain unchanged
}
