#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, OrElse)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    const auto next_result = result.OrElse([](const cait::String&)
                                            { return cait::MakeCorrect<int, cait::String>(42); });

    ASSERT_TRUE(next_result.HasValue());
    ASSERT_EQ(next_result.Get(), 42);
}
