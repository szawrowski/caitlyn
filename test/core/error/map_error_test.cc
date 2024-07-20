#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, MapError) {
  const cait::error::expected_t<int, cait::basic_string_t<char>> result{
      cait::make_failure("Error message")};

  const auto mapped = result.map_error(
      [](const cait::basic_string_t<char>& error) { return error + " fixed"; });

  ASSERT_TRUE(mapped.has_error());
  ASSERT_EQ(mapped.get_error(), "Error message fixed");
}
