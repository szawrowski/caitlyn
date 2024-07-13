#include <gtest/gtest.h>

#include "caitlyn/core/string.h"

TEST(CoreUnicodeTest, StringDefaultInit) {
  const cait::unistring_t str{};
  ASSERT_TRUE(str == "");
}

TEST(CoreUnicodeTest, StringOneCharInit) {
  const cait::unistring_t str{"A"};
  ASSERT_TRUE(str == "A");
}

TEST(CoreUnicodeTest, StringInit) {
  const cait::unistring_t str{"Some string. 🙂"};
  ASSERT_TRUE(str == "Some string. 🙂");
}

TEST(CoreUnicodeTest, StringAssignmentOperator) {
  cait::unistring_t str{};
  str = "Some string. 🙂";
  ASSERT_TRUE(str == "Some string. 🙂");
}

TEST(CoreUnicodeTest, OutputStreamOperator) {
  const cait::unistring_t str = "Some string. 🙂";
  std::ostringstream oss;
  oss << str;

  ASSERT_TRUE(oss.str() == "Some string. 🙂");
}
