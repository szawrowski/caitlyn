#include <gtest/gtest.h>

#include "caitlyn/core/defs/core_definitions.h"

TEST(CoreTest, CaitlynStandardDefinition) {
#if defined(__caitlyn_cxxstd)
  #if (__caitlyn_cxxstd_ver < 11)
    #if defined(__caitlyn_cxxstd_legacy)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxxstd_ver == 11)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd_ver == 14)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd_ver == 17)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd_ver == 20)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd_ver == 23)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd > 23)
    #if defined(__caitlyn_cxxstd_future)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #else
    #if defined(__caitlyn_cxxstd_unknown)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #endif
#endif
}
