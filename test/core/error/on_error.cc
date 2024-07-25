#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, OnError)
{
    const cait::error::expected_t<int, cait::basic_string_t<char>> result{cait::make_failure("Error message")};

    bool error_handled = false;

    result.on_error(
        [&error_handled](const cait::basic_string_t<char>& error)
        {
            error_handled = true;
            ASSERT_EQ(error, "Error message");
        });

    ASSERT_TRUE(error_handled);
}
