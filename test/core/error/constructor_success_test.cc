#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, ConstructorSuccess) {
  const cait::result_t<int, cait::string_t> result{64};

  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.get(), 64);
}
