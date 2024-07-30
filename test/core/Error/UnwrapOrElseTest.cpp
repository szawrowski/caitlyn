#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, UnwrapOrElse)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    ASSERT_EQ(result.UnwrapOrElse([](const Caitlyn::String&) { return 42; }), 42);
}
