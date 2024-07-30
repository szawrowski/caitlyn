#include "Caitlyn/__Serializing/Json.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(JsonTest, TrailingCommaInObject)
{
    const auto config = JSON_STRING({"key" : "value",});
    ASSERT_TRUE(config.HasError());
}

TEST(JsonTest, TrailingCommaInArray)
{
    const auto config = JSON_STRING({"key": [1, 2, 3, 4, 5,]});
    ASSERT_TRUE(config.HasError());
}
