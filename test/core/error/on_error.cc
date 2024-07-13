#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, OnError) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  bool error_handled = false;

  result.on_error([&error_handled](const std::string& error) {
    error_handled = true;
    ASSERT_EQ(error, "Error message");
  });

  ASSERT_TRUE(error_handled);
}
