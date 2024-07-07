#include <gtest/gtest.h>

#include "caitlyn/core/string.h"

TEST(CoreUnicodeTest, StringDefaultInit) {
  const cait::unistr_t str{};
  ASSERT_TRUE(str == "");
}

TEST(CoreUnicodeTest, StringOneCharInit) {
  const cait::unistr_t str{"A"};
  ASSERT_TRUE(str == "A");
}

TEST(CoreUnicodeTest, StringInit) {
  const cait::unistr_t str{"Some string. 🙂"};
  ASSERT_TRUE(str == "Some string. 🙂");
}

TEST(CoreUnicodeTest, StringAssignmentOperator) {
  cait::unistr_t str{};
  str = "Some string. 🙂";
  ASSERT_TRUE(str == "Some string. 🙂");
}

TEST(CoreUnicodeTest, OutputStreamOperator) {
  const cait::unistr_t str = "Some string. 🙂";
  std::basic_ostringstream<cait::u8char_t> oss;
  oss << str;

  ASSERT_TRUE(oss.str() == "Some string. 🙂");
}
