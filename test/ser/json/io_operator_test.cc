#include <gtest/gtest.h>

#include "caitlyn/ser/json.h"
#include "caitlyn/core/io.h"

TEST(JsonTest, IoOperator) {
  const auto oconfig = json_str(
    {
      "name": {
        "first": "John",
        "last": "Doe"
      },
      "age": 30,
      "address": {
        "street": "123 Main St",
        "city": "Anytown",
        "zip": "12345"
      },
      "phone_numbers": [
        "555-1234",
        "555-5678"
      ]
    }
  );
  ASSERT_FALSE(oconfig.has_error());

  std::ofstream ofile{"operator_test.json"};
  if (ofile.is_open()) {
    ofile << oconfig;
    ofile.close();
  }

  auto iconfig = cait::make_json();

  std::ifstream ifile{"operator_test.json"};
  if (ifile.is_open()) {
    ifile >> iconfig;
    ofile.close();
  }

  ASSERT_FALSE(iconfig.has_error());

  ASSERT_STREQ(oconfig.to_string().c_str(),
               iconfig.to_string().c_str());
}