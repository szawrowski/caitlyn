#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, OnError)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> result{Caitlyn::MakeError("Error message")};

    Caitlyn::Bool errorHandled = false;

    result.OnError(
        [&errorHandled](const Caitlyn::String& error)
        {
            errorHandled = true;
            ASSERT_EQ(error, "Error message");
        });

    ASSERT_TRUE(errorHandled);
}
