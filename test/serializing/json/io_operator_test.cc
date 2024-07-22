#include "caitlyn/__serializing/json.h"
#include "caitlyn/__testing/macro.h"

TEST(JsonTest, IoOperator) {
  const auto oconfig = JSON_STRING(
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
  auto iconfig = cait::json::make_document();

  std::ifstream ifile{"operator_test.json"};
  if (ifile.is_open()) {
    ifile >> iconfig;
    ofile.close();
  }

  ASSERT_FALSE(iconfig.has_error());
  std::cout << "OCONFIG:" << oconfig.str() << std::endl;
  std::cout << "ICONFIG:" << iconfig.str() << std::endl;

  ASSERT_EQ(oconfig.str(), iconfig.str());
}