#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, Then)
{
    const auto result = cait::MakeCorrect<int, cait::String>(42);

    const auto next_result =
        result.Then([](const int value) { return cait::MakeCorrect<int, cait::String>(value * 2); });

    ASSERT_TRUE(next_result.HasValue());
    ASSERT_EQ(next_result.Get(), 84);
}
