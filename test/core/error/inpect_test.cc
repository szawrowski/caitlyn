#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, InspectValue)
{
    const auto success_result = cait::make_correct<int, cait::basic_string_t<char>>(42);

    success_result.inspect(
        [](const int value) { ASSERT_EQ(value, 42); },
        [](const cait::basic_string_t<char>&) { FAIL_MESSAGE() << "Expected success"; });
}

TEST(ResultTest, InspectError)
{
    const cait::error::expected_t<int, cait::basic_string_t<char>> error_result{cait::make_failure("Error message")};

    error_result.inspect(
        [](int) { FAIL_MESSAGE() << "Expected error"; },
        [](const cait::basic_string_t<char>& error) { ASSERT_EQ(error, "Error message"); });
}
