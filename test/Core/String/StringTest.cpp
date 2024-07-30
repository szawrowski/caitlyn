#include "Caitlyn/__Core/String.h"
#include "Caitlyn/__Core/IO.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(StringTest, Sample)
{
    Caitlyn::String data = "Hello, 世界! 🙂";

    ASSERT_EQ("世界"_str, data.Substring(7, 2));
    ASSERT_TRUE(data.StartsWith("Hello"));
    ASSERT_TRUE(data.EndsWith("🙂"));
    ASSERT_TRUE(data.Contains("世界"));
    ASSERT_EQ(7, data.Find("世"));
    ASSERT_EQ(11, data.Find("🙂"));
    ASSERT_EQ(10, data.ReverseFind(" "));
    ASSERT_EQ(12, data.Length());
    ASSERT_EQ(19, data.ByteCount());
    ASSERT_EQ(Caitlyn::Char{"e"}, data.At(1));
    ASSERT_EQ(Caitlyn::Char{"!"}, data.At(9));

    for (auto& elem : data)
    {
        if (elem == "🙂")
        {
            elem = "🍉";
        }
    }
    ASSERT_TRUE(data.EndsWith("🍉"));
}
