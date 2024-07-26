#include "Caitlyn/__Serializing/Json.h"
#include "Caitlyn/__Testing/Macro.h"

TEST(JsonTest, InitBracketOperator)
{
    auto config = Caitlyn::Json::MakeDocument();
    config["name"] = Caitlyn::Json::MakeObject();
    config["name"]["first"] = "John";
    config["name"]["last"] = "Doe";
    config["age"] = 30;
    config["address"] = Caitlyn::Json::MakeObject();
    config["address"]["street"] = "123 Main St";
    config["address"]["city"] = "Anytown";
    config["address"]["zip"] = "12345";
    config["phone_numbers"] = Caitlyn::Json::MakeArray("555-1234", "555-5678");

    ASSERT_FALSE(config.HasError());
}

TEST(JsonTest, InitNative)
{
    const auto config = JSON_STRING({
        "name": {"first": "John", "last": "Doe"},
        "age": 30,
        "address": {"street": "123 Main St", "city": "Anytown", "zip": "12345"},
        "phone_numbers": ["555-1234", "555-5678"]
    });
    ASSERT_FALSE(config.HasError());
}
