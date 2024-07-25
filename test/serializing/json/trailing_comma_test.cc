#include "caitlyn/__serializing/json.h"
#include "caitlyn/__testing/macro.h"

TEST(JsonTest, TrailingCommaInObject)
{
    const auto config = JSON_STRING({"key" : "value",});
    ASSERT_TRUE(config.has_error());
}

TEST(JsonTest, TrailingCommaInArray)
{
    const auto config = JSON_STRING({"key": [1, 2, 3, 4, 5,]});
    ASSERT_TRUE(config.has_error());
}
