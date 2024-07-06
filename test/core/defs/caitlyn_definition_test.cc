#include <gtest/gtest.h>

#include "caitlyn/core/defs/core_definitions.h"

TEST(CoreDefsTest, CaitlynDefinition) {
#if defined(__caitlyn__)
  ASSERT_TRUE(true);
#else
  ASSERT_TRUE(false);
#endif
}
