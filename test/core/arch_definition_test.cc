#include <gtest/gtest.h>

#include "caitlyn/core/defs/core_definitions.h"

TEST(CoreTest, ArchDefinition) {
#if defined(__linux__)
  #if !defined(__x86_64__)
    #if defined(__caitlyn_arch32)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #else
    #if defined(__caitlyn_arch64)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #endif
#elif defined(__APPLE__)
  #if !defined(__x86_64__)
    #if defined(__caitlyn_arch32)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #else
    #if defined(__caitlyn_arch64)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #endif
#elif defined(_WIN32)
  #if !defined(_WIN64)
    #if defined(__caitlyn_arch32)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #else
    #if defined(__caitlyn_arch64)
      ASSERT_TRUE(true);
    #else
      ASSERT_TRUE(false);
    #endif
  #endif
#endif
}
