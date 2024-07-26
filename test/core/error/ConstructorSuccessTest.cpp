#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, ConstructorSuccess)
{
    const auto result = cait::Expected<int, cait::String>(64);

    ASSERT_TRUE(result.HasValue());
    ASSERT_EQ(result.Get(), 64);
}
