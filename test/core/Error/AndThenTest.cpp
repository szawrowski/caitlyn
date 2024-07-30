#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, AndThen)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{42};

    const auto nextResult = result.AndThen(
        [](const Caitlyn::Int32 value) { return Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(value * 2); });

    ASSERT_TRUE(nextResult.HasValue());
    ASSERT_EQ(nextResult.Get(), 84);
}
