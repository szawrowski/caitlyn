#include "caitlyn/core/error.h"
#include "caitlyn/test/macro.h"

TEST(ResultTest, FoldValue) {
  const auto result = cait::make_result<int, std::string>(42);

  const auto folded = result.fold(
      10, [](const int acc, const int value) { return acc + value; });

  ASSERT_EQ(folded, 52);
}

TEST(ResultTest, FoldError) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  const auto folded = result.fold(
      10, [](const int acc, const int value) { return acc + value; });

  ASSERT_EQ(folded, 10);  // Initial value should remain unchanged
}
