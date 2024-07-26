#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, Map)
{
    const auto result = cait::MakeCorrect<int, cait::String>(42);
    const auto mapped = result.Map([](const int value) { return value + 1; });

    ASSERT_TRUE(mapped.HasValue());
    ASSERT_EQ(mapped.Get(), 43);
}
