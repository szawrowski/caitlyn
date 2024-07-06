#include <gtest/gtest.h>

#include "caitlyn/core/unicode/char/unicode_char.h"

TEST(CoreUnicodeTest, CharDefaultInit) {
  constexpr cait::char_t symbol{};
  ASSERT_TRUE(symbol == cait::char_t{});
}

TEST(CoreUnicodeTest, CharLetterInit) {
  const cait::char_t symbol{'A'};
  ASSERT_TRUE(symbol == 'A');
}

TEST(CoreUnicodeTest, CharEmojiInit) {
  const cait::char_t emoji{"🙂"};
  ASSERT_TRUE(emoji == "🙂");
}

TEST(CoreUnicodeTest, CharEqOperator) {
  cait::char_t symbol{};
  symbol = 'A';
  ASSERT_TRUE(symbol == cait::char_t{'A'});
}
