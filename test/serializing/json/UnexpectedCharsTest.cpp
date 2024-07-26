#include "Caitlyn/__Serializing/Json.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(JsonTest, UnexpectedCharsFront)
{
    const auto config = JSON_STRING(unexpected {"name": "John Doe", "age": 30});
    ASSERT_TRUE(config.HasError());
}

TEST(JsonTest, UnexpectedCharsBack)
{
    const auto config = JSON_STRING({"name": "John Doe", "age": 30} unexpected);
    ASSERT_TRUE(config.HasError());
}
