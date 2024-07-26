#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, AndThen)
{
    const cait::Expected<int, cait::String> result{42};

    const auto next_result =
        result.AndThen([](const int value) { return cait::MakeCorrect<int, cait::String>(value * 2); });

    ASSERT_TRUE(next_result.HasValue());
    ASSERT_EQ(next_result.Get(), 84);
}
