#include <gtest/gtest.h>

#include "caitlyn/core/unicode/char/unicode_char.h"

TEST(CoreUnicodeTest, CharDefaultInit) {
  constexpr cait::unichar_t symbol{};
  ASSERT_TRUE(symbol == cait::unichar_t{});
}

TEST(CoreUnicodeTest, CharLetterInit) {
  const cait::unichar_t symbol{'A'};
  ASSERT_TRUE(symbol == 'A');
}

TEST(CoreUnicodeTest, CharEmojiInit) {
  const cait::unichar_t emoji{"🙂"};
  ASSERT_TRUE(emoji == "🙂");
}

TEST(CoreUnicodeTest, CharAssignmentOperator) {
  cait::unichar_t symbol{};
  symbol = 'A';
  ASSERT_TRUE(symbol == cait::unichar_t{'A'});
}
