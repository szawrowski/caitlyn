#include "caitlyn/core/error.h"
#include "caitlyn/test.h"

TEST(ResultTest, CatchError) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  const auto caught_result = result.catch_error([](const std::string& error) {
    return cait::make_result<int, std::string>(
        static_cast<int>(error.length()));
  });

  ASSERT_TRUE(caught_result.has_value());
  ASSERT_EQ(caught_result.get(), 13);
}
