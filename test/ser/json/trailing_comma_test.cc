#include "caitlyn/ser/json.h"
#include "caitlyn/test.h"

TEST(JsonTest, TrailingCommaInObject) {
  const auto config = json_str({"key" : "value",});
  ASSERT_TRUE(config.has_error());
}

TEST(JsonTest, TrailingCommaInArray) {
  const auto config = json_str({"key": [1, 2, 3, 4, 5,]});
  ASSERT_TRUE(config.has_error());
}
