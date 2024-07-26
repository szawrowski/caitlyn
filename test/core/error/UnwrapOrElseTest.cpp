#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, UnwrapOrElse)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    ASSERT_EQ(result.UnwrapOrElse([](const cait::String&) { return 42; }), 42);
}
