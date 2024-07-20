#include "caitlyn/__serializing/json.h"
#include "caitlyn/__testing/macro.h"

TEST(JsonTest, UnexpectedCharsFront) {
  const auto config = JSON_STRING(unexpected {"name": "John Doe", "age": 30});
  ASSERT_TRUE(config.has_error());
}

TEST(JsonTest, UnexpectedCharsBack) {
  const auto config = JSON_STRING({"name": "John Doe", "age": 30} unexpected);
  ASSERT_TRUE(config.has_error());
}
