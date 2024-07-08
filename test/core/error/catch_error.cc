#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, CatchError) {
  const cait::result_t<int, cait::string_t> result{
      cait::error_t<cait::string_t>{"Error message"}};

  const auto caught_result =
      result.catch_error([](const cait::string_t& error) {
        return cait::result_t<int, cait::string_t>{
            static_cast<int>(error.length())};
      });

  ASSERT_TRUE(caught_result.has_value());
  ASSERT_EQ(caught_result.get(), 13);
}
