#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, Customize)
{
    const auto result = cait::Expected<int, cait::String>(42);

    const auto custom_result = result.Customize(
        [](const cait::Expected<int, cait::String>& res)
        {
            if (res.HasValue())
            {
                return cait::MakeCorrect<int, cait::String>(res.Get() * 2);
            }
            return cait::Expected<int, cait::String>{cait::MakeError("Custom error")};
        });

    ASSERT_TRUE(custom_result.HasValue());
    ASSERT_EQ(custom_result.Get(), 84);
}
