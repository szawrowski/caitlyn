#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, Map) {
  const auto result = cait::make_result<int, cait::string_t>(42);
  const auto mapped = result.map([](const int value) { return value + 1; });

  ASSERT_TRUE(mapped.has_value());
  ASSERT_EQ(mapped.get(), 43);
}
