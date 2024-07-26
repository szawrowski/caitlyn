#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, CatchError)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    const auto caught_result = result.CatchError(
        [](const cait::String& error)
        { return cait::MakeCorrect<int, cait::String>(static_cast<int>(error.Length())); });

    ASSERT_TRUE(caught_result.HasValue());
    ASSERT_EQ(caught_result.Get(), 13);
}
