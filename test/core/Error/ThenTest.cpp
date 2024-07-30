#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, Then)
{
    const auto result = Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(42);

    const auto nextResult = result.Then([](const Caitlyn::Int32 value)
                                         { return Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(value * 2); });

    ASSERT_TRUE(nextResult.HasValue());
    ASSERT_EQ(nextResult.Get(), 84);
}
