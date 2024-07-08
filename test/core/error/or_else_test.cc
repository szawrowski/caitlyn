#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, OrElse) {
  const cait::result_t<int, cait::string_t> result{
      cait::make_error("Error message")};

  const auto next_result = result.or_else([](const cait::string_t&) {
    return cait::make_result<int, cait::string_t>(42);
  });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 42);
}
