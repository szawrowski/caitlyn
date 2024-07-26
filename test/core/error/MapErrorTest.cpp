#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, MapError)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    const auto mapped = result.MapError([](const Caitlyn::String& error) { return error + " fixed"; });

    ASSERT_TRUE(mapped.HasError());
    ASSERT_EQ(mapped.GetError(), "Error message fixed");
}
