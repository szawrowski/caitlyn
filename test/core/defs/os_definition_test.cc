#include "caitlyn/test/macro.h"

TEST(CoreDefsTest, OsDefinition) {
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
  #if defined(__caitlyn_linux)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#elif defined(__APPLE__)
  #if defined(__caitlyn_apple)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#elif defined(_WIN32)
  #if defined(__caitlyn_windows)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#else
  #if defined(__caitlyn_os_unknown)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#endif
}
