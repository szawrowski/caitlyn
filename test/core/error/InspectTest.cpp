#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, InspectValue)
{
    const auto success_result = cait::MakeCorrect<int, cait::String>(42);

    success_result.Inspect(
        [](const int value) { ASSERT_EQ(value, 42); },
        [](const cait::String&) { FAIL_MESSAGE() << "Expected success"; });
}

TEST(ResultTest, InspectError)
{
    const cait::Expected<int, cait::String> error_result{cait::MakeError("Error message")};

    error_result.Inspect(
        [](int) { FAIL_MESSAGE() << "Expected error"; },
        [](const cait::String& error) { ASSERT_EQ(error, "Error message"); });
}
