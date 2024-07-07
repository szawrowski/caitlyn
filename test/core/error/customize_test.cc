#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, Customize) {
  const cait::result_t<int, cait::string_t> result{42};

  const auto custom_result =
      result.customize([](const cait::result_t<int, cait::string_t>& res) {
        if (res.has_value()) {
          return cait::result_t<int, cait::string_t>{res.get() * 2};
        }
        return cait::result_t<int, cait::string_t>{
            cait::error_t<cait::string_t>{"Custom error"}};
      });

  ASSERT_TRUE(custom_result.has_value());
  ASSERT_EQ(custom_result.get(), 84);
}
