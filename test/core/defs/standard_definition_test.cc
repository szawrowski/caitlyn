#include <gtest/gtest.h>

#include "caitlyn/core/defs/core_definitions.h"

TEST(CoreDefsTest, CaitlynStandardDefinition) {
#if defined(__caitlyn_cxxstd)
  #if (__caitlyn_cxxstd == __caitlyn_cxxstd_legacy_ver)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == __caitlyn_cxxstd11_ver)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == __caitlyn_cxxstd14_ver)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == __caitlyn_cxxstd17_ver)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == __caitlyn_cxxstd20_ver)
    ASSERT_TRUE(true);
  #elif (__caitlyn_cxxstd == __caitlyn_cxxstd23_ver)
    ASSERT_TRUE(true);
  #endif
#endif
}
