#include "caitlyn/core/error.h"
#include "caitlyn/test.h"

TEST(ResultTest, AndThen) {
  const cait::result_t<int, std::string> result{42};

  const auto next_result = result.and_then([](const int value) {
    return cait::make_result<int, std::string>(value * 2);
  });

  ASSERT_TRUE(next_result.has_value());
  ASSERT_EQ(next_result.get(), 84);
}
