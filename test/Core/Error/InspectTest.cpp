#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, InspectValue)
{
    const auto successResult = Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(42);

    successResult.Inspect(
        [](const Caitlyn::Int32 value) { ASSERT_EQ(value, 42); },
        [](const Caitlyn::String&) { FAIL_MESSAGE() << "Expected success"; });
}

TEST(ResultTest, InspectError)
{
    const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String> errorResult{Caitlyn::MakeError("Error message")};

    errorResult.Inspect(
        [](Caitlyn::Int32) { FAIL_MESSAGE() << "Expected error"; },
        [](const Caitlyn::String& error) { ASSERT_EQ(error, "Error message"); });
}
