#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, UnwrapOr) {
  const cait::result_t<int, cait::string_t> result{
      cait::error_t<cait::string_t>{"Error message"}};

  ASSERT_EQ(result.unwrap_or(42), 42);
}
