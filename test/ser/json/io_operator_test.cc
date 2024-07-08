#include <gtest/gtest.h>

#include "caitlyn/ser/json.h"
#include "caitlyn/core/io.h"

TEST(JsonTest, IoOperator) {
  const auto output_config = json_str(
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
  ASSERT_FALSE(output_config.has_error());

  cait::ofstream_t output_file{"operator_test.json"};
  if (output_file.is_open()) {
    output_file << output_config;
    output_file.close();
  }

  auto input_config = cait::make_json();

  cait::ifstream_t input_file{"operator_test.json"};
  if (input_file.is_open()) {
    input_file >> input_config;
    output_file.close();
  }

  ASSERT_FALSE(input_config.has_error());

  ASSERT_STREQ(output_config.to_string().c_str(),
               input_config.to_string().c_str());
}