#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, FoldValue)
{
    const auto result = Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(42);

    const auto folded =
        result.Fold(10, [](const Caitlyn::Int32 acc, const Caitlyn::Int32 value) { return acc + value; });

    ASSERT_EQ(folded, 52);
}

TEST(ResultTest, FoldError)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    const auto folded =
        result.Fold(10, [](const Caitlyn::Int32 acc, const Caitlyn::Int32 value) { return acc + value; });

    ASSERT_EQ(folded, 10); // Initial value should remain unchanged
}
