#include <gtest/gtest.h>

#include "caitlyn/core/defs/core_definitions.h"

TEST(CoreTest, CaitlynStandardDefinition) {
#if defined(__caitlyn_cxxstd)
  #if (__caitlyn_cxxstd < 201103L)
    #if defined(__caitlyn_cxxstd_legacy)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxxstd == 201103L)
    #if defined(__caitlyn_cxxstd11)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxx_standard == 201402L)
    #if defined(__caitlyn_cxx_standard14)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxxstd == 201703L)
    #if defined(__caitlyn_cxxstd17)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxxstd == 202002L)
    #if defined(__caitlyn_cxxstd20)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxxstd == 202302L)
    #if defined(__caitlyn_cxxstd23)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #elif (__caitlyn_cxxstd > 202302L)
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
