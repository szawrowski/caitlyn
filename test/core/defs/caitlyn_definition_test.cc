#include <gtest/gtest.h>

#include "caitlyn/base.h"

TEST(CoreDefsTest, CaitlynDefinition) {
#if defined(__caitlyn__)
  ASSERT_TRUE(true);
#else
  ASSERT_TRUE(false);
#endif
}
