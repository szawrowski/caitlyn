#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, OrElse)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    const auto nextResult =
        result.OrElse([](const Caitlyn::String&) { return Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(42); });

    ASSERT_TRUE(nextResult.HasValue());
    ASSERT_EQ(nextResult.Get(), 42);
}
