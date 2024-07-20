#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, ConstructorError) {
  const cait::error::expected_t<int, cait::basic_string_t<char>> result{
      cait::make_failure("Error message")};

  ASSERT_TRUE(result.has_error());
  ASSERT_EQ(result.get_error(), "Error message");
}
