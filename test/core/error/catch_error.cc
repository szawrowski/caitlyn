#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, CatchError)
{
    const cait::error::expected_t<int, cait::basic_string_t<char>> result{cait::make_failure("Error message")};

    const auto caught_result = result.catch_error(
        [](const cait::basic_string_t<char>& error)
        { return cait::make_correct<int, cait::basic_string_t<char>>(static_cast<int>(error.length())); });

    ASSERT_TRUE(caught_result.has_value());
    ASSERT_EQ(caught_result.get(), 13);
}
