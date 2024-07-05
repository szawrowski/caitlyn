#include <gtest/gtest.h>

#include "caitlyn/core/defs/basic_types.h"

TEST(CoreTest, BasicTypesSizeUnix) {
#if (defined(__caitlyn_linux) || defined(__caitlyn_apple)) && \
    defined(__caitlyn_x64)
  ASSERT_EQ(sizeof(cait::schar_t), 1);
  ASSERT_EQ(sizeof(cait::uchar_t), 1);
  ASSERT_EQ(sizeof(cait::u8char_t), 1);
  ASSERT_EQ(sizeof(cait::u16char_t), 2);
  ASSERT_EQ(sizeof(cait::u32char_t), 4);
  ASSERT_EQ(sizeof(cait::int_t), 4);
  ASSERT_EQ(sizeof(cait::uint_t), 4);
  ASSERT_EQ(sizeof(cait::int8_t), 1);
  ASSERT_EQ(sizeof(cait::uint8_t), 1);
  ASSERT_EQ(sizeof(cait::int16_t), 2);
  ASSERT_EQ(sizeof(cait::uint16_t), 2);
  ASSERT_EQ(sizeof(cait::int32_t), 4);
  ASSERT_EQ(sizeof(cait::uint32_t), 4);
  ASSERT_EQ(sizeof(cait::int64_t), 8);
  ASSERT_EQ(sizeof(cait::uint64_t), 8);
  ASSERT_EQ(sizeof(cait::ptrdiff_t), 8);
  ASSERT_EQ(sizeof(cait::size_t), 8);
  ASSERT_EQ(sizeof(cait::ssize_t), 8);
  ASSERT_EQ(sizeof(cait::float32_t), 4);
  ASSERT_EQ(sizeof(cait::float64_t), 8);
  ASSERT_EQ(sizeof(cait::long_float_t), 16);
  ASSERT_EQ(sizeof(cait::null_t), 8);
#endif
}

TEST(CoreTest, BasicTypesSizeWindows) {
#if defined(__caitlyn_windows) && defined(__caitlyn_x64)
  ASSERT_EQ(sizeof(cait::schar_t), 1);
  ASSERT_EQ(sizeof(cait::uchar_t), 1);
  ASSERT_EQ(sizeof(cait::u8char_t), 1);
  ASSERT_EQ(sizeof(cait::u16char_t), 2);
  ASSERT_EQ(sizeof(cait::u32char_t), 4);
  ASSERT_EQ(sizeof(cait::int_t), 4);
  ASSERT_EQ(sizeof(cait::uint_t), 4);
  ASSERT_EQ(sizeof(cait::int8_t), 1);
  ASSERT_EQ(sizeof(cait::uint8_t), 1);
  ASSERT_EQ(sizeof(cait::int16_t), 2);
  ASSERT_EQ(sizeof(cait::uint16_t), 2);
  ASSERT_EQ(sizeof(cait::int32_t), 4);
  ASSERT_EQ(sizeof(cait::uint32_t), 4);
  ASSERT_EQ(sizeof(cait::int64_t), 8);
  ASSERT_EQ(sizeof(cait::uint64_t), 8);
  ASSERT_EQ(sizeof(cait::ptrdiff_t), 8);
  ASSERT_EQ(sizeof(cait::size_t), 8);
  ASSERT_EQ(sizeof(cait::ssize_t), 8);
  ASSERT_EQ(sizeof(cait::float32_t), 4);
  ASSERT_EQ(sizeof(cait::float64_t), 8);
  ASSERT_EQ(sizeof(cait::long_float_t), 8);
  ASSERT_EQ(sizeof(cait::null_t), 8);
#endif
}
