#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, Then) {
  const auto result = cait::make_result<int, std::string>(42);

  const auto next_result = result.then([](const int value) {
    return cait::make_result<int, std::string>(value * 2);
  });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 84);
}
