#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, FoldValue)
{
    const auto result = cait::MakeCorrect<int, cait::String>(42);

    const auto folded = result.Fold(10, [](const int acc, const int value) { return acc + value; });

    ASSERT_EQ(folded, 52);
}

TEST(ResultTest, FoldError)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    const auto folded = result.Fold(10, [](const int acc, const int value) { return acc + value; });

    ASSERT_EQ(folded, 10); // Initial value should remain unchanged
}
