#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, UnwrapOr) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  ASSERT_EQ(result.unwrap_or(42), 42);
}
