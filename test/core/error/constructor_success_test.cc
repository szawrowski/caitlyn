#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, ConstructorSuccess) {
  const auto result = cait::make_result<int, cait::string_t>(64);

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.get(), 64);
}
