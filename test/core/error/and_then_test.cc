#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, AndThen) {
  const cait::result_t<int, cait::string_t> result{42};

  const auto next_result = result.and_then([](const int value) {
    return cait::result_t<int, cait::string_t>{value * 2};
  });
  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 84);
}
