#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, ConstructorError) {
  const cait::result_t<int, cait::string_t> result{
      cait::make_error("Error message")};

  ASSERT_TRUE(result.has_error());
  ASSERT_EQ(result.get_error(), "Error message");
}
