#include "caitlyn/test.h"

TEST(CoreDefsTest, CompilerDefinition) {
#if defined(__clang__)
  #if defined(__caitlyn_cxxstd) && (__caitlyn_cxxstd == __cplusplus) && \
      defined(__caitlyn_compiler_clang)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#elif (__GNUC__)
  #if defined(__caitlyn_cxxstd) && (__caitlyn_cxxstd == __cplusplus) && \
      defined(__caitlyn_compiler_gcc)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#elif defined(__INTEL_COMPILER) || defined(__ICC)
  #if defined(__caitlyn_cxxstd) && (__caitlyn_cxxstd == __cplusplus) && \
      defined(__caitlyn_compiler_intel)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#elif (_MSC_VER)
  #if defined(__caitlyn_cxxstd) && (__caitlyn_cxxstd == _MSVC_LANG) && \
      defined(__caitlyn_compiler_msvc)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#else
  #if defined(__caitlyn_compiler_unknown)
    ASSERT_TRUE(true);
  #else
    ASSERT_TRUE(false);
  #endif
#endif
}
