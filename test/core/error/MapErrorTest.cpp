#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, MapError)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    const auto mapped = result.MapError([](const cait::String& error) { return error + " fixed"; });

    ASSERT_TRUE(mapped.HasError());
    ASSERT_EQ(mapped.GetError(), "Error message fixed");
}
