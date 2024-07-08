#include <gtest/gtest.h>

#include "caitlyn/core/error.h"
#include "caitlyn/core/string.h"

TEST(ResultTest, UnwrapOrElse) {
  const cait::result_t<int, cait::string_t> result{
      cait::make_error("Error message")};

  ASSERT_EQ(result.unwrap_or_else([](const cait::string_t&) { return 42; }),
            42);
}
