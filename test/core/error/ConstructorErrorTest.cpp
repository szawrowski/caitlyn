#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, ConstructorError)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    ASSERT_TRUE(result.HasError());
    ASSERT_EQ(result.GetError(), "Error message");
}
