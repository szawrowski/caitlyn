#include "caitlyn/__serializing/json.h"
#include "caitlyn/__testing/macro.h"

TEST(JsonTest, InitBracketOperator)
{
    auto config = cait::json::make_document();
    config["name"] = cait::json::make_object();
    config["name"]["first"] = "John";
    config["name"]["last"] = "Doe";
    config["age"] = 30;
    config["address"] = cait::json::make_object();
    config["address"]["street"] = "123 Main St";
    config["address"]["city"] = "Anytown";
    config["address"]["zip"] = "12345";
    config["phone_numbers"] = cait::json::make_array("555-1234", "555-5678");

    ASSERT_FALSE(config.has_error());
}

TEST(JsonTest, InitNative)
{
    const auto config = JSON_STRING({
        "name": {"first": "John", "last": "Doe"},
        "age": 30,
        "address": {"street": "123 Main St", "city": "Anytown", "zip": "12345"},
        "phone_numbers": ["555-1234", "555-5678"]
    });
    ASSERT_FALSE(config.has_error());
}
