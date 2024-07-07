#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, ConstructorError) {
  const cait::result_t<int, cait::string_t> result{
      cait::error_t<cait::string_t>{"Error message"}};

  ASSERT_TRUE(result.has_error());
  ASSERT_EQ(result.get_error(), "Error message");
}
