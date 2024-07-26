#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, UnwrapOr)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    ASSERT_EQ(result.UnwrapOr(42), 42);
}
