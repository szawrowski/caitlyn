#include "caitlyn/core/unicode.h"
#include "caitlyn/test.h"

TEST(CoreUnicodeTest, StringDefaultInit) {
  const cait::unistring_t str{};
  ASSERT_EQ(str, "");
}

TEST(CoreUnicodeTest, StringOneCharInit) {
  const cait::unistring_t str{"A"};
  ASSERT_EQ(str, "A");
}

TEST(CoreUnicodeTest, StringInit) {
  const cait::unistring_t str{"Some string. 🙂"};
  ASSERT_EQ(str, "Some string. 🙂");
}

TEST(CoreUnicodeTest, StringAssignmentOperator) {
  cait::unistring_t str{};
  str = "Some string. 🙂";
  ASSERT_EQ(str, "Some string. 🙂");
}

TEST(CoreUnicodeTest, OutputStreamOperator) {
  const cait::unistring_t str = "Some string. 🙂";
  std::ostringstream oss;
  oss << str;

  ASSERT_EQ(oss.str(), "Some string. 🙂");
}
