#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, CatchError)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    const auto caughtResult = result.CatchError(
        [](const Caitlyn::String& error)
        { return Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(static_cast<Caitlyn::Int32>(error.Length())); });

    ASSERT_TRUE(caughtResult.HasValue());
    ASSERT_EQ(caughtResult.Get(), 13);
}
