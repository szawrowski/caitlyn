#include "caitlyn/core/unicode.h"
#include "caitlyn/test.h"

TEST(CoreUnicodeTest, CharDefaultInit) {
  constexpr cait::unichar_t symbol{};
  ASSERT_EQ(symbol, cait::unichar_t{});
}

TEST(CoreUnicodeTest, CharLetterInit) {
  const cait::unichar_t symbol{'A'};
  ASSERT_EQ(symbol, 'A');
}

TEST(CoreUnicodeTest, CharEmojiInit) {
  const cait::unichar_t emoji{"🙂"};
  ASSERT_EQ(emoji, "🙂");
}

TEST(CoreUnicodeTest, CharAssignmentOperator) {
  cait::unichar_t symbol{};
  symbol = 'A';
  ASSERT_EQ(symbol, 'A');
}
