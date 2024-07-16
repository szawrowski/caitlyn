#include "caitlyn/core/error.h"
#include "caitlyn/test/macro.h"

TEST(ResultTest, InspectValue) {
  const auto success_result = cait::make_result<int, std::string>(42);

  success_result.inspect(
      [](const int value) { ASSERT_EQ(value, 42); },
      [](const std::string&) { FAIL_MESSAGE() << "Expected success"; });
}

TEST(ResultTest, InspectError) {
  const cait::result_t<int, std::string> error_result{
      cait::make_error("Error message")};

  error_result.inspect(
      [](int) { FAIL_MESSAGE() << "Expected error"; },
      [](const std::string& error) { ASSERT_EQ(error, "Error message"); });
}
