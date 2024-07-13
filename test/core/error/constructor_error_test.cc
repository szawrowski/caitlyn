#include "caitlyn/core/error.h"
#include "caitlyn/test.h"

TEST(ResultTest, ConstructorError) {
  const cait::result_t<int, std::string> result{
      cait::make_error("Error message")};

  ASSERT_TRUE(result.has_error());
  ASSERT_EQ(result.get_error(), "Error message");
}
