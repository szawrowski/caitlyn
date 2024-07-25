#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, FoldValue)
{
    const auto result = cait::make_correct<int, cait::basic_string_t<char>>(42);

    const auto folded = result.fold(10, [](const int acc, const int value) { return acc + value; });

    ASSERT_EQ(folded, 52);
}

TEST(ResultTest, FoldError)
{
    const cait::error::expected_t<int, cait::basic_string_t<char>> result{cait::make_failure("Error message")};

    const auto folded = result.fold(10, [](const int acc, const int value) { return acc + value; });

    ASSERT_EQ(folded, 10); // Initial value should remain unchanged
}
