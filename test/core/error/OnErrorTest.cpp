#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, OnError)
{
    const cait::Expected<int, cait::String> result{cait::MakeError("Error message")};

    bool error_handled = false;

    result.OnError(
        [&error_handled](const cait::String& error)
        {
            error_handled = true;
            ASSERT_EQ(error, "Error message");
        });

    ASSERT_TRUE(error_handled);
}
