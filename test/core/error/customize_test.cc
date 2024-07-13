#include "caitlyn/core/error.h"
#include "caitlyn/test.h"

TEST(ResultTest, Customize) {
  const auto result = cait::result_t<int, std::string>(42);

  const auto custom_result =
      result.customize([](const cait::result_t<int, std::string>& res) {
        if (res.has_value()) {
          return cait::make_result<int, std::string>(res.get() * 2);
        }
        return cait::result_t<int, std::string>{
            cait::make_error("Custom error")};
      });

  ASSERT_TRUE(custom_result.has_value());
  ASSERT_EQ(custom_result.get(), 84);
}
