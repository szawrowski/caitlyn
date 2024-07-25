#include "caitlyn/__core/error.h"
#include "caitlyn/__testing/macro.h"

TEST(ResultTest, ConstructorSuccess)
{
    const auto result = cait::error::expected_t<int, cait::basic_string_t<char>>(64);

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.get(), 64);
}
