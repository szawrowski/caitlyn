#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, MapError) {
  const cait::result_t<int, cait::string_t> result{
      cait::error_t<cait::string_t>{"Error message"}};

  const auto mapped = result.map_error(
      [](const cait::string_t& error) { return error + " fixed"; });

  ASSERT_TRUE(mapped.has_error());
  ASSERT_EQ(mapped.get_error(), "Error message fixed");
}