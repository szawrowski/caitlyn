#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, OrElse)
{
    const cait::error::expected_t<int, cait::basic_string_t<char>> result{cait::make_failure("Error message")};

    const auto next_result = result.or_else([](const cait::basic_string_t<char>&)
                                            { return cait::make_correct<int, cait::basic_string_t<char>>(42); });

    ASSERT_TRUE(next_result.has_value());
    ASSERT_EQ(next_result.get(), 42);
}
