#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, UnwrapOr) {
  const cait::result_t<int, cait::string_t> result{
      cait::make_error("Error message")};

  ASSERT_EQ(result.unwrap_or(42), 42);
}
