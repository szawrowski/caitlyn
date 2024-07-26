#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, Map)
{
    const auto result = Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(42);
    const auto mapped = result.Map([](const Caitlyn::Int32 value) { return value + 1; });

    ASSERT_TRUE(mapped.HasValue());
    ASSERT_EQ(mapped.Get(), 43);
}
