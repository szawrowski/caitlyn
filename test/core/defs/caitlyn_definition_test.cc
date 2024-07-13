#include "caitlyn/test.h"

TEST(CoreDefsTest, CaitlynDefinition) {
#if defined(__caitlyn__)
  ASSERT_TRUE(true);
#else
  ASSERT_TRUE(false);
#endif
}
