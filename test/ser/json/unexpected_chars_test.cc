#include "caitlyn/ser/json.h"
#include "caitlyn/test/macro.h"

TEST(JsonTest, UnexpectedCharsFront) {
  const auto config = json_str(unexpected {"name": "John Doe","age": 30});
  ASSERT_TRUE(config.has_error());
}

TEST(JsonTest, UnexpectedCharsBack) {
  const auto config = json_str({"name": "John Doe","age": 30} unexpected);
  ASSERT_TRUE(config.has_error());
}
