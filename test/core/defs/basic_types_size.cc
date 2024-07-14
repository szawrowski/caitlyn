#include "caitlyn/test.h"

TEST(CoreDefsTest, BasicTypesSizeUnix) {
#if defined(__caitlyn_unix) && (__caitlyn_arch == 64)
  ASSERT_EQ(sizeof(cait::char_t), 1);
  ASSERT_EQ(sizeof(cait::schar_t), 1);
  ASSERT_EQ(sizeof(cait::uchar_t), 1);
  ASSERT_EQ(sizeof(cait::u8char_t), 1);
  ASSERT_EQ(sizeof(cait::u16char_t), 2);
  ASSERT_EQ(sizeof(cait::u32char_t), 4);
  ASSERT_EQ(sizeof(cait::byte_t), 1);
  ASSERT_EQ(sizeof(cait::sbyte_t), 1);
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
  ASSERT_EQ(sizeof(cait::floatx_t), 16);
  ASSERT_EQ(sizeof(cait::null_t), 8);
#endif
}

TEST(CoreDefsTest, BasicTypesSizeWindows) {
#if defined(__caitlyn_windows) && (__caitlyn_arch == 64)
  ASSERT_EQ(sizeof(cait::schar_t), 1);
  ASSERT_EQ(sizeof(cait::uchar_t), 1);
  ASSERT_EQ(sizeof(cait::u8char_t), 1);
  ASSERT_EQ(sizeof(cait::u16char_t), 2);
  ASSERT_EQ(sizeof(cait::u32char_t), 4);
  ASSERT_EQ(sizeof(cait::byte_t), 1);
  ASSERT_EQ(sizeof(cait::sbyte_t), 1);
  ASSERT_EQ(sizeof(cait::ssize_t), 8);
  ASSERT_EQ(sizeof(cait::float32_t), 4);
  ASSERT_EQ(sizeof(cait::float64_t), 8);
  ASSERT_EQ(sizeof(cait::floatx_t), 8);
#endif
}
