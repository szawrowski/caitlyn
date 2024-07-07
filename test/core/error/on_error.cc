#include <gtest/gtest.h>

#include "caitlyn/core/error.h"

TEST(ResultTest, OnError) {
  const cait::result_t<int, cait::string_t> result{
      cait::error_t<cait::string_t>{"Error message"}};

  bool error_handled = false;

  result.on_error([&error_handled](const cait::string_t& error) {
    error_handled = true;
    ASSERT_EQ(error, "Error message");
  });

  ASSERT_TRUE(error_handled);
}
