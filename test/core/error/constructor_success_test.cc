#include "caitlyn/core/error.h"
#include "caitlyn/test/macro.h"

TEST(ResultTest, ConstructorSuccess) {
  const auto result = cait::make_result<int, std::string>(64);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.get(), 64);
}
