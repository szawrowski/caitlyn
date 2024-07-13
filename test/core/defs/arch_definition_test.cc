#include "caitlyn/test.h"

TEST(CoreDefsTest, ArchDefinition) {
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
  #if !defined(__x86_64__)
    ASSERT_EQ(__caitlyn_arch, 32);
  #else
    ASSERT_EQ(__caitlyn_arch, 64);
  #endif
#elif defined(__APPLE__)
  #if !defined(__x86_64__)
    ASSERT_EQ(__caitlyn_arch, 32);
  #else
    ASSERT_EQ(__caitlyn_arch, 64);
  #endif
#elif defined(_WIN32)
  #if !defined(_WIN64)
    ASSERT_EQ(__caitlyn_arch, 32)
  #else
    ASSERT_EQ(__caitlyn_arch, 64);
  #endif
#endif
}
