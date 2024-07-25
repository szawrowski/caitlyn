#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, Customize)
{
    const auto result = cait::error::expected_t<int, cait::basic_string_t<char>>(42);

    const auto custom_result = result.customize(
        [](const cait::error::expected_t<int, cait::basic_string_t<char>>& res)
        {
            if (res.has_value())
            {
                return cait::make_correct<int, cait::basic_string_t<char>>(res.get() * 2);
            }
            return cait::error::expected_t<int, cait::basic_string_t<char>>{cait::make_failure("Custom error")};
        });

    ASSERT_TRUE(custom_result.has_value());
    ASSERT_EQ(custom_result.get(), 84);
}
