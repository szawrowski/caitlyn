#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, InspectValue) {
  const auto success_result = cait::make_result<int, cait::string_t>(42);

  success_result.inspect(
      [](const int value) { ASSERT_EQ(value, 42); },
      [](const cait::string_t&) { FAIL() << "Expected success"; });
}

TEST(ResultTest, InspectError) {
  const cait::result_t<int, cait::string_t> error_result{
      cait::make_error("Error message")};

  error_result.inspect(
      [](int) { FAIL() << "Expected error"; },
      [](const cait::string_t& error) { ASSERT_EQ(error, "Error message"); });
}
