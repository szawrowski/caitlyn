#include "Caitlyn/__Core/Error.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(ResultTest, Customize)
{
    const auto result = Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String>(42);

    const auto customResult = result.Customize(
        [](const Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String>& res)
        {
            if (res.HasValue())
            {
                return Caitlyn::MakeCorrect<Caitlyn::Int32, Caitlyn::String>(res.Get() * 2);
            }
            return Caitlyn::Expected<Caitlyn::Int32, Caitlyn::String>{Caitlyn::MakeError("Custom error")};
        });

    ASSERT_TRUE(customResult.HasValue());
    ASSERT_EQ(customResult.Get(), 84);
}
