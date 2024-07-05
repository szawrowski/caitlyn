#include <gtest/gtest.h>

#include "caitlyn/core/defs/core_definitions.h"

TEST(CoreTest, CaitlynStandardDefinition) {
#if defined(__caitlyn_cxxstd)
  #if (__caitlyn_cxxstd == 11)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == 14)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == 17)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == 20)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == 23)
    ASSERT_TRUE(true);
  #endif
#endif
}
