#include "caitlyn/core/error.h"
#include "caitlyn/test.h"

TEST(ResultTest, UnwrapOrElse) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  ASSERT_EQ(result.unwrap_or_else([](const std::string&) { return 42; }), 42);
}
