#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, ConstructorError)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    ASSERT_TRUE(result.HasError());
    ASSERT_EQ(result.GetError(), "Error message");
}
