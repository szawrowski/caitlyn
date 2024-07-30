#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, ConstructorSuccess)
{
    const auto result = Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String>(64);

    ASSERT_TRUE(result.HasValue());
    ASSERT_EQ(result.Get(), 64);
}
