#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, MapError) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  const auto mapped = result.map_error(
      [](const std::string& error) { return error + " fixed"; });

  ASSERT_TRUE(mapped.has_error());
  ASSERT_EQ(mapped.get_error(), "Error message fixed");
}
