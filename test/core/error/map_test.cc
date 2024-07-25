#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, Map)
{
    const auto result = cait::make_correct<int, cait::basic_string_t<char>>(42);
    const auto mapped = result.map([](const int value) { return value + 1; });

    ASSERT_TRUE(mapped.has_value());
    ASSERT_EQ(mapped.get(), 43);
}
