#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, Then) {
  const cait::result_t<int, cait::string_t> result{42};

  const auto next_result = result.then([](const int value) {
    return cait::result_t<int, cait::string_t>{value * 2};
  });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 84);
}
