#include "caitlyn/test.h"

TEST(CoreDefsTest, CaitlynStandardDefinition) {
#if defined(__caitlyn_cxxstd)
  #if __caitlyn_has_cxx98
    ASSERT_TRUE(true);
  #elif __caitlyn_has_cxx11
    ASSERT_TRUE(true);
  #elif __caitlyn_has_cxx14
    ASSERT_TRUE(true);
  #elif __caitlyn_has_cxx17
    ASSERT_TRUE(true);
  #elif __caitlyn_has_cxx20
    ASSERT_TRUE(true);
  #elif __caitlyn_has_cxx23
    ASSERT_TRUE(true);
  #endif
#endif
}
