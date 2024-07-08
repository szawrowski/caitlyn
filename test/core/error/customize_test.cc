#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, Customize) {
  const auto result = cait::result_t<int, cait::string_t>(42);

  const auto custom_result =
      result.customize([](const cait::result_t<int, cait::string_t>& res) {
        if (res.has_value()) {
          return cait::make_result<int, cait::string_t>(res.get() * 2);
        }
        return cait::result_t<int, cait::string_t>{
            cait::make_error("Custom error")};
      });

  ASSERT_TRUE(custom_result.has_value());
  ASSERT_EQ(custom_result.get(), 84);
}
